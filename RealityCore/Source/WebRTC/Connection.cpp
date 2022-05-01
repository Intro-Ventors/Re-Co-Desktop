// Copyright (c) 2022 Intro-Ventors

#include "Connection.hpp"

#include <chrono>
#include <execution>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace WebRTC
{
	Connection::Connection(rtc::Configuration&& config)
	{
		m_WebSocket.onOpen([] {});
		m_WebSocket.onClosed([] {});
		m_WebSocket.onError([](const std::string& error) {});
		m_WebSocket.onMessage([this, &config](rtc::variant<rtc::binary, std::string> data)
			{
				if (!std::holds_alternative<std::string>(data))
					return;

				json message = json::parse(std::get<std::string>(data));
				m_Reactor.issueCommand([this, message, config] { setupConnection(config, message); });
			}
		);

		m_WebSocket.open("ws://127.0.0.1:8080");

		while (!m_WebSocket.isOpen()) {
			if (m_WebSocket.isClosed())
				return;

			using namespace std::chrono_literals;
			std::this_thread::sleep_for(100ms);
		}
	}

	void Connection::submitImage(const std::byte* pImage, uint64_t width, uint64_t height, uint8_t bitsPerPixel)
	{
		// Just skip if we don't need to record.
		if (!m_ShouldRecord)
			return;

		m_Sample.resize(width * height * 4);
		std::copy(std::execution::par, pImage, pImage + m_Sample.size(), m_Sample.begin());

		m_SampleTimeUs = Internal::clock::now();
	}

	void Connection::stop()
	{
		m_ShouldRecord = false;
	}

	void Connection::start()
	{
		m_ShouldRecord = true;
	}

	void Connection::loadNextSample()
	{
	}

	void Connection::setupConnection(const rtc::Configuration& config, const json& document)
	{
		auto itr = document.find("id");
		if (itr == document.end())
			return;

		std::string id = itr->get<std::string>();
		itr = document.find("type");

		if (itr == document.end())
			return;

		const auto type = itr->get<std::string>();
		if (type == "streamRequest")
		{
			auto pc = std::make_shared<rtc::PeerConnection>(config);
			auto client = std::make_shared<Internal::Client>(pc);

			pc->onStateChange([this, id](rtc::PeerConnection::State state)
				{
					if (state == rtc::PeerConnection::State::Disconnected ||
						state == rtc::PeerConnection::State::Failed ||
						state == rtc::PeerConnection::State::Closed)
					{
						// remove disconnected client
						m_Reactor.issueCommand([this, id] { m_Clients.erase(id); });
					}
				}
			);

			pc->onGatheringStateChange([this, id, &pc](rtc::PeerConnection::GatheringState state)
				{
					if (state == rtc::PeerConnection::GatheringState::Complete)
					{
						auto description = pc->localDescription();
						json message = {
							{"id", id},
							{"type", description->typeString()},
							{"sdp", std::string(description.value())}
						};

						// Gathering complete, send answer
						m_WebSocket.send(message.dump());
					}
				}
			);

			// Create video stream.
			client->m_Video = createVideo(pc.get(), client.get());

			pc->setLocalDescription();
			m_Clients.emplace(id, client);
		}
		else if (type == "answer")
		{
			if (auto jt = m_Clients.find(id); jt != m_Clients.end()) 
			{
				auto pc = m_Clients.at(id)->m_PeerConnectionRef;
				auto sdp = document["sdp"].get<std::string>();
				auto description = rtc::Description(sdp, type);
				pc->setRemoteDescription(description);
			}
		}
	}

	std::optional<std::shared_ptr<Internal::ClientTrackData>> Connection::createVideo(rtc::PeerConnection* pPeerConnection, Internal::Client* pClient)
	{
		constexpr auto payloadType = 102;
		constexpr auto ssrc = 1;
		constexpr auto msid = "stream1";
		constexpr auto cname = "video-stream";

		auto video = rtc::Description::Video(cname);
		video.addH264Codec(payloadType);
		video.addSSRC(ssrc, cname, msid, cname);
		auto track = pPeerConnection->addTrack(video);

		auto rtpConfig = std::make_shared<rtc::RtpPacketizationConfig>(ssrc, cname, payloadType, rtc::H264RtpPacketizer::defaultClockRate);
		auto packetizer = std::make_shared<rtc::H264RtpPacketizer>(rtc::H264RtpPacketizer::Separator::Length, rtpConfig);
		auto h264Handler = std::make_shared<rtc::H264PacketizationHandler>(std::make_shared<rtc::H264RtpPacketizer>(rtc::H264RtpPacketizer::Separator::Length, rtpConfig));

		auto srReporter = std::make_shared<rtc::RtcpSrReporter>(rtpConfig);
		h264Handler->addToChain(srReporter);
		h264Handler->addToChain(std::make_shared<rtc::RtcpNackResponder>());

		track->setMediaHandler(h264Handler);
		track->onOpen([this, pClient] { m_Reactor.issueCommand([this, pClient] { onTrackOpen(pClient); }); });

		return std::make_shared<Internal::ClientTrackData>(track, srReporter);
	}

	void Connection::onTrackOpen(Internal::Client* pClient)
	{
		if (pClient->getState() == Internal::Client::State::Waiting)
			pClient->setState(Internal::Client::State::WaitingForVideo);

		else if (pClient->getState() == Internal::Client::State::WaitingForVideo)
		{
			// Video tracks are collected now
			assert(pClient->m_Video.has_value());

			const auto& video = pClient->m_Video.value();
			auto currentTime_us = double(Internal::clock::now().time_since_epoch().count());
			auto currentTime_s = currentTime_us / (1000 * 1000);

			// set start time of stream
			video->m_Sender->rtpConfig->setStartTime(currentTime_s, rtc::RtpPacketizationConfig::EpochStart::T1970);

			// start stat recording of RTCP SR
			video->m_Sender->startRecording();

			if (m_VideoStream.has_value())
			{
				std::vector<std::byte> imageData(1280 * 720 * 4);
				video->m_Sender->rtpConfig->timestamp = 0;
				video->m_Track->send(imageData);
				video->m_Sender->rtpConfig->timestamp += 0;

				video->m_Track->send(imageData);
			}

			pClient->setState(Internal::Client::State::Ready);
		}

		if (pClient->getState() == Internal::Client::State::Ready)
		{
			std::shared_ptr<Internal::Stream> stream;
			if (m_VideoStream.has_value())
			{
				stream = m_VideoStream.value();
				if (stream->m_IsRunningRef)
				{
					// stream is already running
					return;
				}
			}
			else
			{
				m_VideoStream = std::make_shared<Internal::Stream>(shared_from_this());

				stream->onSample([this, stream](Internal::Stream::StreamSourceType type, uint64_t sampleTime, rtc::binary sample)
					{
						std::vector<Internal::ClientTrack> tracks;

						// get all clients with Ready state
						for (const auto& id_client : m_Clients)
						{
							const auto& id = id_client.first;
							const auto& client = id_client.second;

							if (client->getState() == Internal::Client::State::Ready && client->m_Video)
								tracks.emplace_back(id, client->m_Video.value());
						}

						if (!tracks.empty())
						{
							for (auto& clientTrack : tracks)
							{
								auto trackData = clientTrack.m_TrackData;
								auto elapsedSeconds = double(sampleTime) / (1000 * 1000);
								auto rtpConfig = trackData->m_Sender->rtpConfig;
								auto elapsedTimestamp = rtpConfig->secondsToTimestamp(elapsedSeconds);

								rtpConfig->timestamp = rtpConfig->startTimestamp + elapsedTimestamp;

								// get elapsed time in clock rate from last RTCP sender report
								auto reportElapsedTimestamp = rtpConfig->timestamp - trackData->m_Sender->previousReportedTimestamp;
								// check if last report was at least 1 second ago
								if (rtpConfig->timestampToSeconds(reportElapsedTimestamp) > 1)
									trackData->m_Sender->setNeedsToReport();

								bool send = false;
								try
								{
									// send sample
									send = trackData->m_Track->send(sample);
								}
								catch (...)
								{
									send = false;
								}
								if (!send) {
									break;
								}
							}
						}

						m_Reactor.issueCommand([this, stream]
							{
								if (m_Clients.empty())
									stream->stop();
							}
						);
					}
				);
			}

			stream->start();
		}
	}
}