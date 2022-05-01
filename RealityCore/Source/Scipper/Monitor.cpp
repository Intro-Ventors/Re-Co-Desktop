// Copyright (c) 2022 Intro-Ventors

#include "Monitor.hpp"

namespace Scipper
{
	Monitor::Monitor(QString name)
		: FrameCapture(std::move(name))
	{
		// Create the capture configuration.
		m_pConfiguration = SL::Screen_Capture::CreateCaptureConfiguration([this]() -> std::vector<SL::Screen_Capture::Monitor>
			{
				// Get the monitors.
				const auto monitors = SL::Screen_Capture::GetMonitors();

				// Just skip searching if the name is null or empty.
				if (!m_Name.isEmpty())
				{
					// Get the windows and iterate over them.
					for (auto const& monitor : monitors)
					{
						// We have selected this as the required monitor.
						if (m_Name == monitor.Name)
							return { monitor };
					}
				}

				// Return the monitors if nothing found.
				return monitors;
			}
		)->onNewFrame([this](const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Monitor& monitor) { onNewFrame(image, monitor); }
		)->start_capturing();

		using namespace std::chrono_literals;
		m_pConfiguration->setFrameChangeInterval(1ms);
	}

	void Monitor::onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Monitor& monitor)
	{
		Q_UNUSED(monitor);

		// Compute the time delta.
		const auto tick = Clock::now();
		const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(tick.time_since_epoch() - m_TimePoint.time_since_epoch());

		// Submit the image to the client(s).
		m_pConnection->submitImage(reinterpret_cast<const std::byte*>(image.Data), monitor.Width, monitor.Height);

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