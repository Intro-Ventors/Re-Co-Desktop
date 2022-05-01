// Copyright (c) 2022 Intro-Ventors

#pragma once

#include <rtc/rtc.hpp>

#include "Internal/Client.hpp"

namespace WebRTC
{
	/**
	 * Connection class.
	 */
	class Connection final : public std::enable_shared_from_this<Connection>, public Internal::StreamSource
	{
	public:
		enum class State : uint8_t
		{
			Waiting,
			WaitingForVideo,
			WaitingForAudio,
			Ready
		};

		/**
		 * Constructor.
		 *
		 * @param config The connection configuration.
		 */
		explicit Connection(const rtc::Configuration& config);

		/**
		 * Submit an image to the connection and send it to the client.
		 *
		 * @param pImage The image pointer.
		 * @param width The image width.
		 * @param height The image height.
		 * @param bitsPerPixel The number of bits per pixel. Since we are uploading in BGRA, it'll most probably be 8.
		 */
		void submitImage(const std::byte* pImage, uint64_t width, uint64_t height, uint8_t bitsPerPixel = 8);

		/**
		 * Stop streaming.
		 */
		void stop() override;

		/**
		 * Start streaming.
		 */
		void start() override;

		/**
		 * Load the next sample to send.
		 */
		void loadNextSample() override;

	private:
		Reactor m_Reactor;
		std::string m_ConnectionID;
		rtc::WebSocket m_WebSocket;

		std::unordered_map<std::string, std::shared_ptr<Internal::Client>> m_Clients;

		std::optional<std::shared_ptr<Internal::Stream>> m_VideoStream = std::nullopt;

		std::shared_mutex m_SharedMutex;
		State m_State = State::Waiting;
	};
}