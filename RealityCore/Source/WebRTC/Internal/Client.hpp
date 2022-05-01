// Copyright (c) 2022 Intro-Ventors

#pragma once

#include "Stream.hpp"

#include <shared_mutex>

namespace WebRTC
{
	namespace Internal
	{
		/**
		 * Client track data struct.
		 */
		struct ClientTrackData final
		{
			std::shared_ptr<rtc::Track> m_Track;
			std::shared_ptr<rtc::RtcpSrReporter> m_Sender;

			/**
			 * Explicit constructor.
			 *
			 * @param track The track pointer.
			 * @param sender the sender pointer.
			 */
			explicit ClientTrackData(const std::shared_ptr<rtc::Track>& track, const std::shared_ptr<rtc::RtcpSrReporter>& sender) : m_Track(track), m_Sender(sender) {}
		};

		/**
		 * Client structure.
		 */
		struct Client final
		{
			enum class State {
				Waiting,
				WaitingForVideo,
				WaitingForAudio,
				Ready
			};

			/**
			 * Explicit constructor.
			 *
			 * @param pc The peer connection pointer.
			 */
			explicit Client(const std::shared_ptr<rtc::PeerConnection>& pc) : m_PeerConnection(pc) { }

			/**
			 * Set the current state.
			 *
			 * @param state The state to set.
			 */
			void setState(State state);

			/**
			 * Get the current state.
			 *
			 * @return The state.
			 */
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

		/**
		 * Client track structure.
		 */
		struct ClientTrack
		{
			std::string m_ID;
			std::shared_ptr<ClientTrackData> m_TrackData;

			/**
			 * Explicit constructor.
			 *
			 * @param id The ID of the track.
			 * @param trackData The track data.
			 */
			explicit ClientTrack(std::string id, std::shared_ptr<ClientTrackData> trackData) : m_ID(id), m_TrackData(trackData) {}
		};
	}
}