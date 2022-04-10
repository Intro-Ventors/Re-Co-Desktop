// Copyright (c) 2022 Intro-Ventors

#include "Instance.hpp"

#include <condition_variable>

namespace Scipper
{
	namespace /* anonymous */
	{
		/**
		 * Dummy function to handle the new frame.
		 * This function is needed because without it, we cannot get the available window titles.
		 *
		 * @param NONE
		 * @param NONE
		 */
		void dummyNewFrameHandler_Window(const SL::Screen_Capture::Image&, const SL::Screen_Capture::Window&) {}

		/**
		 * Dummy function to handle the new frame.
		 * This function is needed because without it, we cannot get the available monitor titles.
		 *
		 * @param NONE
		 * @param NONE
		 */
		void dummyNewFrameHandler_Monitor(const SL::Screen_Capture::Image&, const SL::Screen_Capture::Monitor&) {}
	}

	void Instance::refreshTitles()
	{
		refreshWindowTitles();
		refreshMonitorTitles();
	}

	std::vector<std::shared_ptr<Window>>& Instance::refreshWindows(int limit)
	{
		// Refresh all the titles so we get the latest ones.
		refreshWindowTitles();

		// Clear the screens if they are not empty.
		if (!m_Windows.empty())
			m_Windows.clear();

		// Create the new screens.
		for (auto& title : m_WindowTitles)
		{
			if (!title.isEmpty() && limit > 0)
			{
				m_Windows.emplace_back(std::make_shared<Window>(title));
				limit--;
			}
		}

		return m_Windows;
	}

	std::vector<std::shared_ptr<Monitor>>& Instance::refreshMonitors()
	{
		// Refresh all the titles so we get the latest ones.
		refreshMonitorTitles();

		// Clear the monitors if they are not empty.
		if (!m_Monitors.empty())
			m_Monitors.clear();

		// Create all the new monitors.
		for (auto& title : m_MonitorTitles)
			if (!title.isEmpty())
				m_Monitors.emplace_back(std::make_shared<Monitor>(title));

		return m_Monitors;
	}

	void Instance::refreshWindowTitles()
	{
		// Clear the window titles if data is present.
		if (m_WindowTitles.size())
			m_WindowTitles.clear();

		// Setup the synchronization variables.
		std::condition_variable condition = {};
		std::mutex resourceMutex = {};
		bool bState = true;

		// Create the dummy capture configuration to get the window titles.
		// This is the only way to get the window names because by directly calling the GetWindows() function will result in a corrupted stack.
		const auto configuration = SL::Screen_Capture::CreateCaptureConfiguration([&condition, &resourceMutex, &bState, this]
			{
				// Lock the resources and wait till we can proceed.
				auto lock = std::unique_lock(resourceMutex);
				condition.wait(lock, [&bState] { return !bState; });

				// Get the windows.
				const auto windows = SL::Screen_Capture::GetWindows();

				// Get the windows and iterate over them.
				m_WindowTitles.reserve(windows.size());
				for (auto const& window : windows)
					m_WindowTitles.emplace_back(window.Name);

				// Notify the parent thread to continue executing.
				bState = true;
				lock.unlock();
				condition.notify_one();

				// Return the windows afterwards.
				return SL::Screen_Capture::GetWindows();
			}
		)->onNewFrame(dummyNewFrameHandler_Window)->start_capturing();

		// Signal the configuration to proceed.
		{
			auto lock = std::scoped_lock(resourceMutex);
			bState = false;
			condition.notify_one();
		}

		// Again wait till the configuration finishes its work for us to continue.
		{
			auto lock = std::unique_lock(resourceMutex);
			condition.wait(lock, [&bState] { return bState; });
		}
	}

	void Instance::refreshMonitorTitles()
	{
		// Clear the monitor titles if data is present.
		if (m_MonitorTitles.size())
			m_MonitorTitles.clear();

		// Setup the synchronization variables.
		std::condition_variable condition = {};
		std::mutex resourceMutex = {};
		bool bState = true;

		// Create the dummy capture configuration to get the monitor titles.
		// This is the only way to get the monitor names because by directly calling the GetMonitors() function will result in a corrupted stack.
		const auto configuration = SL::Screen_Capture::CreateCaptureConfiguration([&condition, &resourceMutex, &bState, this]
			{
				// Lock the resources and wait till we can proceed.
				auto lock = std::unique_lock(resourceMutex);
				condition.wait(lock, [&bState] { return !bState; });

				// Get the monitors.
				const auto monitors = SL::Screen_Capture::GetMonitors();

				// Get the monitors and iterate over them.
				m_MonitorTitles.reserve(monitors.size());
				for (auto const& monitor : monitors)
					m_MonitorTitles.emplace_back(monitor.Name);

				// Notify the parent thread to continue executing.
				bState = true;
				lock.unlock();
				condition.notify_one();

				// Return the windows afterwards.
				return monitors;
			}
		)->onNewFrame(dummyNewFrameHandler_Monitor)->start_capturing();

		// Signal the configuration to proceed.
		{
			auto lock = std::scoped_lock(resourceMutex);
			bState = false;
			condition.notify_one();
		}

		// Again wait till the configuration finishes its work for us to continue.
		{
			auto lock = std::unique_lock(resourceMutex);
			condition.wait(lock, [&bState] { return bState; });
		}
	}
}