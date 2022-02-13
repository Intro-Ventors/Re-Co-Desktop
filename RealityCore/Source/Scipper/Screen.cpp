#include "Screen.hpp"

#include <condition_variable>
#include <semaphore>
#include <QPixmap>

namespace Scipper
{
	Screen::Screen(QString name)
		: m_Name(std::move(name))
	{
		// Create the sync object.
		std::condition_variable conditional = {};

		// Create the capture configuration.
		p_Configuration = SL::Screen_Capture::CreateCaptureConfiguration([&conditional, this]() -> std::vector<SL::Screen_Capture::Window>
			{
				// Get the windows.
				const auto windows = SL::Screen_Capture::GetWindows();

				// Just skip searching if the name is null or empty.
				if (m_Name.isEmpty())
				{
					// Notify the parent thread to continue and return.
					conditional.notify_one();
					return windows;
				}

				// Get the windows and iterate over them.
				for (auto const& window : windows)
				{
					// We have selected this as the required window.
					if (m_Name == window.Name)
					{
						// Notify the parent thread to continue and return.
						conditional.notify_one();
						return { window };
					}
				}

				// Notify the parent thread to continue.
				conditional.notify_one();

				// Return the windows if nothing found.
				return windows;
			}
			//)->onFrameChanged([this](const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window) { onFrameChanged(image, window); }
		)->onNewFrame([this](const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window) { onNewFrame(image, window); }
			//)->onMouseChanged([this](const SL::Screen_Capture::Image* pImage, const SL::Screen_Capture::MousePoint& mousePoint) { onMouseChanged(pImage, mousePoint); }
		)->start_capturing();

		using namespace std::chrono_literals;
		p_Configuration->setFrameChangeInterval(35ms);

		// Wait till the thread has completed execution.
		std::mutex mutex;
		auto lock = std::unique_lock(mutex);
		conditional.wait(lock);
	}

	void Screen::onFrameChanged(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
		image;
		window;
	}

	void Screen::onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
		// If we can record, convert the image data to RGBA and then send it to the receiving end.
		if (b_ShouldRecord)
		{
			// Convert the image.
			convertRGBA(image);

			// Emit the new frame signal.
			emit newFrame(p_ImageData);

			b_ShouldRecord = false;
		}
	}

	void Screen::onMouseChanged(const SL::Screen_Capture::Image* pImage, const SL::Screen_Capture::MousePoint& mousePoint)
	{
		pImage;
		mousePoint;
	}

	void Screen::convertRGBA(const SL::Screen_Capture::Image& image)
	{
		const auto width = Width(image);
		const auto height = Height(image);
		p_ImageData = std::make_shared<ImageData>(std::make_shared<uchar[]>(width * height * 4), width, height);


		auto imgsrc = StartSrc(image);
		auto imgdist = p_ImageData->p_ImageData.get();
		for (auto h = 0; h < height; h++)
		{
			auto startimgsrc = imgsrc;
			for (auto w = 0; w < width; w++)
			{
				*imgdist++ = imgsrc->R;
				*imgdist++ = imgsrc->G;
				*imgdist++ = imgsrc->B;
				*imgdist++ = imgsrc->A;
				imgsrc++;
			}

			imgsrc = SL::Screen_Capture::GotoNextRow(image, startimgsrc);
		}
	}
}