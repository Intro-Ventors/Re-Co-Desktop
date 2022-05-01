// Copyright (c) 2022 Intro-Ventors

#include "Client.hpp"

namespace WebRTC
{
	namespace Internal
	{
		void Client::setState(State state)
		{
			std::unique_lock lock(m_Mutex);
			m_State = state;
		}

		Client::State Client::getState()
		{
			std::shared_lock lock(m_Mutex);
			return m_State;
		}
	}
}