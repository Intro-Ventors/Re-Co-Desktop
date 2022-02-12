#include "Screen.hpp"

namespace Scipper
{
	Screen::Screen(QString name) : m_Name(std::move(name))
	{
		// Create the capture configuration.
		p_Configuration = SL::Screen_Capture::CreateCaptureConfiguration([this]() -> std::vector<SL::Screen_Capture::Window>
			{
				// Get the windows.
				const auto windows = SL::Screen_Capture::GetWindows();

				// Get the windows and iterate over them.
				for (auto const& window : windows)
				{
					// We have selected this as the required window.
					if (m_Name == window.Name)
					{
						return { window };
					}
				}

				// Return the windows afterwards.
				return SL::Screen_Capture::GetWindows();
			})->onFrameChanged([this](const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window) { onFrameChanged(image, window); }
			)->onNewFrame([this](const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window) { onNewFrame(image, window); }
			)->onMouseChanged([this](const SL::Screen_Capture::Image* pImage, const SL::Screen_Capture::MousePoint& mousePoint) { onMouseChanged(pImage, mousePoint); }
			)->start_capturing();
	}

	void Screen::onFrameChanged(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
	}

	void Screen::onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
	}

	void Screen::onMouseChanged(const SL::Screen_Capture::Image* pImage, const SL::Screen_Capture::MousePoint& mousePoint)
	{
	}
}