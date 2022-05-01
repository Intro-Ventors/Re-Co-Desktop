// Copyright (c) 2022 Intro-Ventors

#pragma once

#include <rtc/rtc.hpp>
#include <chrono>

#include "../Reactor.hpp"

namespace WebRTC
{
	namespace Internal
	{
		using clock = std::chrono::high_resolution_clock;

		/**
		 * Stream source class.
		 */
		class StreamSource
		{
		protected:
			clock::time_point m_SampleTimeUs;
			rtc::binary m_Sample = {};

		public:
			StreamSource() = default;
			virtual ~StreamSource();

			virtual void stop();
			virtual void start() = 0;
			virtual void loadNextSample() = 0;

			clock::time_point getSampleTime_us() const { return m_SampleTimeUs; }
			rtc::binary getSample() const { return m_Sample; }
		};

		class Stream final : public std::enable_shared_from_this<Stream>
		{
			clock::duration m_StartTime;
			std::mutex m_Mutex;
			WebRTC::Reactor m_Reactor = WebRTC::Reactor();

			bool m_IsRunning = false;

		public:
			enum class StreamSourceType : uint8_t {
				Audio,
				Video
			};

			const std::shared_ptr<StreamSource> m_Video;

			Stream(std::shared_ptr<StreamSource> video) : m_Video(video) {}
			~Stream() { stop(); }

		private:
			rtc::synchronized_callback<StreamSourceType, uint64_t, rtc::binary> m_SampleHandler;

			std::pair<std::shared_ptr<StreamSource>, StreamSourceType> unsafePrepareForSample();
			void sendSample();

		public:
			void onSample(std::function<void(StreamSourceType, uint64_t, rtc::binary)> handler) { m_SampleHandler = handler; }
			void start();
			void stop();

			const bool& m_IsRunningRef = m_IsRunning;
		};
	}
}