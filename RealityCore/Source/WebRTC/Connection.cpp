#include "Connection.hpp"

namespace WebRTC
{
	Connection::Connection(rtc::Configuration config)
		: m_PeerConnection(config)
	{
		// Setup on state change handler.
		m_PeerConnection.onStateChange([this](rtc::PeerConnection::State state)
			{
				switch (state)
				{
				case rtc::PeerConnection::State::New:
					break;
				case rtc::PeerConnection::State::Connecting:
					break;
				case rtc::PeerConnection::State::Connected:
					break;
				case rtc::PeerConnection::State::Disconnected:
					break;
				case rtc::PeerConnection::State::Failed:
					break;
				case rtc::PeerConnection::State::Closed:
					break;
				default:
					break;
				}
			}
		);

		// Setup on gathering state change handler.
		m_PeerConnection.onGatheringStateChange([this](rtc::PeerConnection::GatheringState state)
			{
				switch (state)
				{
				case rtc::PeerConnection::GatheringState::New:
					break;
				case rtc::PeerConnection::GatheringState::InProgress:
					break;
				case rtc::PeerConnection::GatheringState::Complete:
					break;
				default:
					break;
				}
			}
		);

		// Create the data channel.
		m_pVideDataChannel = m_PeerConnection.createDataChannel("capture");

		// Setup the data channel open handler.
		m_pVideDataChannel->onOpen([this]
			{
				m_pVideDataChannel->send("Welcome!");
			}
		);

		// Setup the data channel on message handler.
		m_pVideDataChannel->onMessage([this](const rtc::binary& binary)
			{
				m_pVideDataChannel->send("Received data with size: " + std::to_string(binary.size()));
			},
			[this](const std::string& message)
			{
				m_pVideDataChannel->send("Received message: " + message);
			}
			);

		m_PeerConnection.setLocalDescription();
	}
}