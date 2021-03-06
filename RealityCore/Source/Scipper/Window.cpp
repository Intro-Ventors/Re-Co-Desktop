// Copyright (c) 2022 Intro-Ventors

#include "Window.hpp"

namespace Scipper
{
	Window::Window(QString name)
		: FrameCapture(std::move(name))
	{
		// Create the capture configuration.
		m_pConfiguration = SL::Screen_Capture::CreateCaptureConfiguration([this]() -> std::vector<SL::Screen_Capture::Window>
			{
				// Get the windows.
				const auto windows = SL::Screen_Capture::GetWindows();

				// Just skip searching if the name is null or empty.
				if (!m_Name.isEmpty())
				{
					// Get the windows and iterate over them.
					for (auto const& window : windows)
					{
						// We have selected this as the required window.
						if (m_Name == window.Name)
							return { window };
					}
				}

				// Return the windows if nothing found.
				return windows;
			}
		)->onNewFrame([this](const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window) { onNewFrame(image, window); }
		)->start_capturing();

		using namespace std::chrono_literals;
		m_pConfiguration->setFrameChangeInterval(1ms);
	}

	void Window::onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
		Q_UNUSED(window);

		// Compute the time delta.
		const auto tick = Clock::now();
		const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(tick.time_since_epoch() - m_TimePoint.time_since_epoch());

		// Make sure to only convert and create the image if a slot is connected.
		if (receivers(SIGNAL(newFrame(std::shared_ptr<ImageData>))) > 0)
		{
			// If we can record, convert the image data to RGBA and then send it to the receiving end.
			if (m_bShouldRecord)
			{
				// Convert the image.
				m_pImageData = convertRGBA(image, delta.count());

				// Emit the new frame signal.
				emit newFrame(m_pImageData);

				// Toggle should record bool.
				m_bShouldRecord = false;
			}
			else
			{
				// Get the delta time.
				m_pImageData->m_DeltaTime = delta.count();
			}
		}

		m_TimePoint = tick;
	}
}