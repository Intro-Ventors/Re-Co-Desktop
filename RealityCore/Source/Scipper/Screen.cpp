#include "Screen.hpp"

#include <condition_variable>
#include <semaphore>
#include <future>

#include <lodepng.h>

namespace Scipper
{
	Screen::Screen(QString name)
		: m_Name(std::move(name))
	{
		// Create the sync object.
		std::condition_variable conditional = {};

		// Create the capture configuration.
		m_pConfiguration = SL::Screen_Capture::CreateCaptureConfiguration([&conditional, this]() -> std::vector<SL::Screen_Capture::Window>
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
		m_pConfiguration->setFrameChangeInterval(35ms);

		// Wait till the thread has completed execution.
		std::mutex mutex;
		auto lock = std::unique_lock(mutex);
		conditional.wait(lock);
	}

	void Screen::onFrameChanged(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
		Q_UNUSED(image);
		Q_UNUSED(window);
	}

	void Screen::onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window)
	{
		Q_UNUSED(window);

		// Compute the time delta.
		const auto tick = Clock::now();
		const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(tick.time_since_epoch() - m_TimePoint.time_since_epoch());

		// Asynchronously execute the encoding command.
		//auto thread = std::thread([&image, this]
		//	{
		//		// Encode the image to PNG.
		//		const auto encodedImage = convertPNG(image);
		//
		//		// Send the data to the client.
		//
		//		// Make sure to free the allocated memory afterwards.
		//		std::free(encodedImage.p_Data);
		//	}
		//);
		//
		//thread.detach();

		// If we can record, convert the image data to RGBA and then send it to the receiving end.
		if (m_bShouldRecord)
		{
			// Convert the image.
			m_pImageData = std::move(convertRGBA(image, delta.count()));

			m_pImageData->m_DeltaTime = delta.count();

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

		m_TimePoint = tick;
	}

	void Screen::onMouseChanged(const SL::Screen_Capture::Image* pImage, const SL::Screen_Capture::MousePoint& mousePoint)
	{
		Q_UNUSED(pImage);
		Q_UNUSED(mousePoint);
	}

	std::shared_ptr<ImageData> Screen::convertRGBA(const SL::Screen_Capture::Image& image, const uint64_t delta)
	{
		// Get the width and height of the image.
		const auto width = Width(image);
		const auto height = Height(image);

		// Create the new image data.
		auto pImageData = std::make_shared<ImageData>(std::make_shared<uchar[]>(width * height * 4), width, height, delta);

		// Iterate through the image data and convert the data from BGRA to RGBA.
		auto pImageSource = StartSrc(image);
		auto pImageDestination = pImageData->p_ImageData.get();
		for (auto h = 0; h < height; h++)
		{
			auto pStartImageSource = pImageSource;
			for (auto w = 0; w < width; w++)
			{
				*pImageDestination++ = pImageSource->R;
				*pImageDestination++ = pImageSource->G;
				*pImageDestination++ = pImageSource->B;
				*pImageDestination++ = pImageSource->A;
				pImageSource++;
			}

			pImageSource = SL::Screen_Capture::GotoNextRow(image, pStartImageSource);
		}

		return pImageData;
	}

	std::shared_ptr<ImageData> Screen::convertRGBA_Test(const SL::Screen_Capture::Image& image, const uint64_t delta)
	{
		// Get the width and height of the image.
		const auto width = Width(image);
		const auto height = Height(image);

		// Create the new image data.
		return std::make_shared<ImageData>(nullptr, 0, 0, delta);
	}

	EncodedImage Screen::convertPNG(const ImageData* pImageData)
	{
		EncodedImage image = {};

		// Encode the data. If it was successful, the return would be zero. If not it'll be any other value.
		if (lodepng_encode_memory(&image.p_Data, &image.m_Size, pImageData->p_ImageData.get(), pImageData->m_Width, pImageData->m_Height, LodePNGColorType::LCT_RGBA, 8))
		{
			// Handle the error.
		}

		return image;
	}

	EncodedImage Screen::convertPNG(const SL::Screen_Capture::Image& image)
	{
		EncodedImage encodedImage = {};

		// Encode the data. If it was successful, the return would be zero. If not it'll be any other value.
		if (lodepng_encode_memory(&encodedImage.p_Data, &encodedImage.m_Size, reinterpret_cast<const uchar*>(StartSrc(image)), Width(image), Height(image), LodePNGColorType::LCT_RGBA, 8))
		{
			// Handle the error.
		}

		return encodedImage;
	}
}