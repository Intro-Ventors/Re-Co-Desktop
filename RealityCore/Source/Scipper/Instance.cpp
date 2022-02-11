#include "Instance.hpp"

#include <ScreenCapture.h>
#include <condition_variable>

namespace Scipper
{
	namespace
	{
		/**
		 * Dummy function to handle the frame change.
		 * This function is needed because without it, we cannot get the available screen titles.
		 *
		 * @param NONE
		 * @param NONE
		 */
		void dummyFrameChangeHandler(const SL::Screen_Capture::Image&, const SL::Screen_Capture::Window&) {}

		/**
		 * Dummy function to handle the new frame.
		 * This function is needed because without it, we cannot get the available screen titles.
		 *
		 * @param NONE
		 * @param NONE
		 */
		void dummyNewFrameHandler(const SL::Screen_Capture::Image&, const SL::Screen_Capture::Window&) {}

		/**
		 * Dummy function to handle the mouse change.
		 * This function is needed because without it, we cannot get the available screen titles.
		 *
		 * @param NONE
		 * @param NONE
		 */
		void dummyMouseChangeHandler(const SL::Screen_Capture::Image*, const SL::Screen_Capture::MousePoint&) {}
	}

	Instance::Instance()
	{
		// Refresh the titles to get the current titles.
		refreshTitles();
	}

	void Instance::refreshTitles()
	{
		// Clear the screen titles if data is present.
		if (m_ScreenTitles.size())
			m_ScreenTitles.clear();

		// Setup the synchronization variables.
		std::condition_variable condition = {};
		std::mutex resourceMutex = {};
		bool bState = true;

		// Create the dummy capture configuration to get the window titles.
		// This is the only way to get the window names because by directly calling the GetWindows() function will result in a corrupted stack.
		const auto configuration = SL::Screen_Capture::CreateCaptureConfiguration([&, this]
			{
				// Lock the resources and wait till we can proceed.
				auto lock = std::unique_lock(resourceMutex);
				condition.wait(lock, [&bState] { return !bState; });

				// Get the windows.
				const auto windows = SL::Screen_Capture::GetWindows();

				// Get the windows and iterate over them.
				for (auto const& window : windows)
					m_ScreenTitles.emplace_back(window.Name);

				// Notify the parent thread to continue executing.
				bState = true;
				lock.unlock();
				condition.notify_one();

				// Return the windows afterwards.
				return SL::Screen_Capture::GetWindows();
			}
		)->onFrameChanged(dummyFrameChangeHandler)->onNewFrame(dummyNewFrameHandler)->onMouseChanged(dummyMouseChangeHandler)->start_capturing();

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