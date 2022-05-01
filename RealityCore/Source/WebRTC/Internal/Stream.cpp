// Copyright (c) 2022 Intro-Ventors

#include "Stream.hpp"

namespace WebRTC
{
	namespace Internal
	{
		StreamSource::~StreamSource()
		{
			stop();
		}

		void StreamSource::stop()
		{
			m_SampleTimeUs = {};
			m_Sample = {};
		}
		
		std::pair<std::shared_ptr<StreamSource>, Stream::StreamSourceType> Stream::unsafePrepareForSample()
		{
			std::shared_ptr<StreamSource> ss;
			StreamSourceType sst;
			ss = m_Video;
			sst = StreamSourceType::Video;
			const auto nextTime = m_Video->getSampleTime_us().time_since_epoch();
			const auto currentTime = std::chrono::high_resolution_clock::now().time_since_epoch();

			auto elapsed = currentTime - m_StartTime;
			if (nextTime > elapsed)
			{
				const auto waitTime = nextTime - elapsed;
				const auto lock = std::scoped_lock(m_Mutex);

				std::this_thread::sleep_for(waitTime);
			}

			return { ss, sst };
		}
		
		void Stream::sendSample()
		{
			std::lock_guard lock(m_Mutex);
			if (!m_IsRunningRef)
				return;

			const auto ssSST = unsafePrepareForSample();
			const auto ss = ssSST.first;
			const auto sst = ssSST.second;
			const auto sample = ss->getSample();
			m_SampleHandler(sst, ss->getSampleTime_us().time_since_epoch().count(), sample);
			ss->loadNextSample();
			m_Reactor.issueCommand([this] {this->sendSample(); });
		}
		
		void Stream::start()
		{
			std::lock_guard lock(m_Mutex);
			if (m_IsRunningRef) {
				return;
			}

			m_IsRunning = true;
			m_StartTime = std::chrono::high_resolution_clock::now().time_since_epoch();
			m_Video->start();
			m_Reactor.issueCommand([this] { this->sendSample(); });
		}

		void Stream::stop()
		{
			std::lock_guard lock(m_Mutex);
			if (!m_IsRunningRef)
				return;

			m_IsRunning = false;
			m_Reactor.clear();
			m_Video->stop();
		};
	}
}