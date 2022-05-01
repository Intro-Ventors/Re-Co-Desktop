// Copyright (c) 2022 Intro-Ventors

#include "FrameCapture.hpp"

#include <algorithm>
#include <execution>
#include <future>

#include <lodepng.h>

namespace Scipper
{
	FrameCapture::FrameCapture(QString name)
		: m_Name(name)
	{
		rtc::Configuration configuration;
		configuration.iceServers.emplace_back("stun:stun.l.google.com:19302");
		configuration.disableAutoNegotiation = true;

		m_pConnection = std::make_shared<WebRTC::Connection>(std::move(configuration));
	}

	std::shared_ptr<ImageData> FrameCapture::convertRGBA(const SL::Screen_Capture::Image& image, const uint64_t delta)
	{
		// Get the width and height of the image.
		const size_t width = Width(image);
		const size_t height = Height(image);

		// Create the new image data.
		auto pImageData = std::make_shared<ImageData>(std::vector<RGBA8>(width * height), width, height, delta);

		// Get the image source.
		auto pImageSource = StartSrc(image);

		// Transform the image from BGRA to RGBA using the parallel policy.
		std::transform(std::execution::parallel_unsequenced_policy(), pImageSource, pImageSource + (width * height), pImageData->p_ImageData.begin(), [](const SL::Screen_Capture::ImageBGRA& source)
			{
				RGBA8 destination = {};
				destination.R = source.R;
				destination.G = source.G;
				destination.B = source.B;
				destination.A = source.A;

				return destination;
			}
		);

		return pImageData;
	}

	std::shared_ptr<ImageData> FrameCapture::convertRGBA_Test(const SL::Screen_Capture::Image& image, const uint64_t delta)
	{
		Q_UNUSED(image);

		// Create the new image data.
		return std::make_shared<ImageData>(std::vector<RGBA8>(), 0, 0, delta);
	}

	EncodedImage FrameCapture::convertPNG(const ImageData* pImageData)
	{
		EncodedImage image = {};

		// Encode the data. If it was successful, the return would be zero. If not it'll be any other value.
		if (lodepng_encode_memory(&image.p_Data, &image.m_Size, reinterpret_cast<const uint8_t*>(pImageData->p_ImageData.data()), pImageData->m_Width, pImageData->m_Height, LodePNGColorType::LCT_RGBA, 8))
		{
			// Handle the error.
		}

		return image;
	}

	EncodedImage FrameCapture::convertPNG(const SL::Screen_Capture::Image& image)
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
