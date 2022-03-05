#pragma once

#include <rtc/peerconnection.hpp>
#include <shared_mutex>
#include "Reactor.hpp"

namespace WebRTC
{
	/**
	 * Connection class.
	 */
	class Connection
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
		explicit Connection(rtc::Configuration config);

	private:
		Reactor m_Reactor;
		std::string m_ConnectionID;
		rtc::PeerConnection m_PeerConnection;
		std::shared_ptr<rtc::DataChannel> m_pVideDataChannel = nullptr;
		std::shared_mutex m_SharedMutex;
		State m_State = State::Waiting;
	};
}