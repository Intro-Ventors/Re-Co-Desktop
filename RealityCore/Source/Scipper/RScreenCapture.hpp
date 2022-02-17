#pragma once

#include <cstdint>
#include <vector>

namespace Scipper
{
	/**
	 * Reality Core screen capture abstract class.
	 * This class is the base class for all the classes in the screen capture API.
	 */
	class RScreenCapture
	{
	public:
		/**
		 * Default constructor.
		 */
		RScreenCapture() = default;

		/**
		 * Default virtual destructor.
		 */
		virtual ~RScreenCapture() = 0;
	};

	/**
	 * RGBA8 structure.
	 * This structure represents a single pixel of data.
	 */
	struct RGBA8 { uint8_t R, G, B, A; };

	/**
	 * Image data struct.
	 * This structure contains the information needed to render the image to the widget.
	 */
	struct ImageData
	{
		ImageData(const std::vector<RGBA8>& pData, uint32_t width, uint32_t height, uint64_t delta = 0) : p_ImageData(std::move(pData)), m_Width(width), m_Height(height), m_DeltaTime(delta) {}

		std::vector<RGBA8> p_ImageData = {};
		uint64_t m_DeltaTime = 0;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};

	/**
	 * Encoded image struct.
	 * This struct contains the information regarding the PNG encoded image.
	 */
	struct EncodedImage
	{
		uint8_t* p_Data = nullptr;
		size_t m_Size = 0;
	};
}