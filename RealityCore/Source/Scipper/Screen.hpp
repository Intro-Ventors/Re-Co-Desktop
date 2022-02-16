#pragma once

#include "RScreenCapture.hpp"

#include <ScreenCapture.h>
#include <QString>
#include <QLabel>
#include <atomic>

namespace Scipper
{
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
		uchar* p_Data = nullptr;
		size_t m_Size = 0;
	};

	/**
	 * Screen class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Screen final : public QObject, public RScreenCapture
	{
		Q_OBJECT

	public:
		using ScreenCaptureConfig = std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager>;
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		/**
		 * Constructor.
		 *
		 * @param name The name of the screen.
		 */
		Screen(QString name);

		/**
		 * Toggle the record boolean.
		 */
		void toggleRecord() { m_bShouldRecord = true; }

	signals:
		/**
		 * Signal indicating that a new frame was added.
		 *
		 * @param image The new image.
		 */
		void newFrame(std::shared_ptr<ImageData> image);

	private:
		/**
		 * Function to handle frame changed.
		 *
		 * @param image The frame image.
		 * @param window The window in which the new frame is captured.
		 */
		void onFrameChanged(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window);

		/**
		 * Function to handle new frame.
		 *
		 * @param image The frame image.
		 * @param window The window in which the new frame is captured.
		 */
		void onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window);

		/**
		 * Function to handle mouse change event.
		 *
		 * @param pImage The image pointer.
		 * @param mousePoint The mouse point.
		 */
		void onMouseChanged(const SL::Screen_Capture::Image* pImage, const SL::Screen_Capture::MousePoint& mousePoint);

	private:
		/**
		 * Convert the BGRA image to RGBA.
		 *
		 * @param image The image reference.
		 * @param delta The time delta between the current frame and the old frame.
		 * @return The converted data.
		 */
		static std::shared_ptr<ImageData> convertRGBA(const SL::Screen_Capture::Image& image, const uint64_t delta);

		/**
		 * Convert the BGRA image to RGBA.
		 *
		 * @param image The image reference.
		 * @param delta The time delta between the current frame and the old frame.
		 * @return The converted data.
		 */
		static std::shared_ptr<ImageData> convertRGBA_Test(const SL::Screen_Capture::Image& image, const uint64_t delta);

		/**
		 * Convert the incoming image data to a PNG format.
		 *
		 * @param pImageData The image data to encode.
		 * @return The encoded image.
		 */
		static EncodedImage convertPNG(const ImageData* pImageData);

		/**
		 * Convert the incoming image data to a PNG format.
		 *
		 * @param image The image data from the Screen Capture Lite API.
		 * @return The encoded image.
		 */
		static EncodedImage convertPNG(const SL::Screen_Capture::Image& image);

	private:
		QString m_Name;
		QImage m_Image;
		ScreenCaptureConfig m_pConfiguration = nullptr;
		std::atomic<bool> m_bShouldRecord = true;
		std::shared_ptr<ImageData> m_pImageData = nullptr;
		TimePoint m_TimePoint;
	};
}