#include "DuplicationThread.hpp"

#include <lodepng.h>
#include <algorithm>
#include <execution>

namespace Scipper
{
	DuplicationThread::DuplicationThread()
	{
		/*
		m_Thread = std::jthread([this]
			{
				// Create the desktop duplication object.
				m_pDesktopDuplication = std::make_unique<DesktopDuplication>();

				// Get the current time point. This variable is used to store and get the difference between each iteration.
				auto timePoint = std::chrono::high_resolution_clock::now();

				// Main capture loop.
				while (m_bShouldRun)
				{
					auto newTime = std::chrono::high_resolution_clock::now();
					emit tick(newTime - timePoint);

					// Capture a new image.
					const auto data = m_pDesktopDuplication->capture();

					// Create the new buffer to store the converted data.
					auto imageData = std::vector<RGBA8>(data.m_Width * data.m_Height);

					// Iterate over the buffer and get the correct data.
					//for (auto itr = data.m_Buffer.begin(); itr != data.m_Buffer.end(); itr++, imageItr++)
					//{
					//	imageItr->R = itr->R;
					//	imageItr->G = itr->G;
					//	imageItr->B = itr->B;
					//	imageItr->A = itr->A;
					//}

					std::transform(std::execution::parallel_unsequenced_policy(), data.m_Buffer.begin(), data.m_Buffer.end(), imageData.begin(), [](const BGRA8& lhs)
						{
							RGBA8 rhs = {};
							rhs.R = lhs.R;
							rhs.G = lhs.G;
							rhs.B = lhs.B;
							rhs.A = lhs.A;

							return rhs;
						}
					);

					//uchar* pData = nullptr;
					//size_t size = 0;
					//
					//// Encode the data. If it was successful, the return would be zero. If not it'll be any other value.
					//if (lodepng_encode_memory(&pData, &size, reinterpret_cast<const uint8_t*>(data.m_Buffer.data()), data.m_Width, data.m_Height, LodePNGColorType::LCT_RGBA, 8))
					//{
					//	// Handle the error.
					//}
					//
					//std::free(pData);

					// Emit the image.
					emit image(DuplicationImage(std::move(imageData), data.m_Width, data.m_Height));

					// Assign the new time to the time point variable.
					timePoint = newTime;
				}
			}
		);
		*/
	}
}