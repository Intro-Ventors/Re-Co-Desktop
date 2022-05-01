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
		 * Stream source base class.
		 * All the sources needs to inherit this and be used to stream data back to the user.
		 */
		class StreamSource
		{
		protected:
			clock::time_point m_SampleTimeUs;
			rtc::binary m_Sample = {};

		public:
			/**
			 * Default constructor.
			 */
			StreamSource() = default;

			/**
			 * Virtual destructor.
			 */
			virtual ~StreamSource();

			/**
			 * Stop the stream.
			 */
			virtual void stop();

			/**
			 * Start the stream.
			 */
			virtual void start() = 0;

			/**
			 * Load the next sample to show.
			 */
			virtual void loadNextSample() = 0;

			/**
			 * Get the sample time in micro seconds.
			 *
			 * @return The time.
			 */
			clock::time_point getSampleTime_us() const { return m_SampleTimeUs; }

			/**
			 * Get the binary data sample.
			 *
			 * @return The binary data.
			 */
			rtc::binary getSample() const { return m_Sample; }
		};

		/**
		 * Stream class.
		 * This is used to upload data to the client.
		 */
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

			/**
			 * Explicit constructor.
			 *
			 * @param video The video stream.
			 */
			explicit Stream(const std::shared_ptr<StreamSource>& video) : m_Video(video) {}

			/**
			 * Destructor.
			 */
			~Stream() { stop(); }

		private:
			rtc::synchronized_callback<StreamSourceType, uint64_t, rtc::binary> m_SampleHandler;

			/**
			 * Prepare the stream for a sample, and can be unsafe.
			 *
			 * @return The stream source and the stream source type.
			 */
			std::pair<std::shared_ptr<StreamSource>, StreamSourceType> unsafePrepareForSample();

			/**
			 * Send a sample to the client(s).
			 */
			void sendSample();

		public:
			/**
			 * Handle on sample.
			 *
			 * @param handler The handler function.
			 */
			void onSample(const std::function<void(StreamSourceType, uint64_t, rtc::binary)>& handler) { m_SampleHandler = handler; }

			/**
			 * Start streaming.
			 */
			void start();

			/**
			 * Stop streaming.
			 */
			void stop();

			const bool& m_IsRunningRef = m_IsRunning;
		};
	}
}