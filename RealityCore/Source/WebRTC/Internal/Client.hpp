// Copyright (c) 2022 Intro-Ventors

#pragma once

#include "Stream.hpp"

#include <shared_mutex>

namespace WebRTC
{
	namespace Internal
	{
		struct ClientTrackData final
		{
			std::shared_ptr<rtc::Track> m_Track;
			std::shared_ptr<rtc::RtcpSrReporter> m_Sender;

			ClientTrackData(const std::shared_ptr<rtc::Track>& track, const std::shared_ptr<rtc::RtcpSrReporter>& sender) : m_Track(track), m_Sender(sender) {}
		};

		struct Client final
		{
			enum class State {
				Waiting,
				WaitingForVideo,
				WaitingForAudio,
				Ready
			};
			explicit Client(const std::shared_ptr<rtc::PeerConnection>& pc) : m_PeerConnection(pc) { }

			void setState(State state);
			State getState();

			std::optional<std::shared_ptr<ClientTrackData>> m_Video;
			std::optional<std::shared_ptr<rtc::DataChannel>> m_DataChannel;
			const std::shared_ptr<rtc::PeerConnection>& m_PeerConnectionRef = m_PeerConnection;

		private:
			std::shared_mutex m_Mutex;
			State m_State = State::Waiting;
			std::string m_ID;
			std::shared_ptr<rtc::PeerConnection> m_PeerConnection;
		};

		struct ClientTrack 
		{
			std::string m_ID;
			std::shared_ptr<ClientTrackData> m_TrackData;

			explicit ClientTrack(std::string id, std::shared_ptr<ClientTrackData> trackData) : m_ID(id), m_TrackData(trackData) {}
		};
	}
}