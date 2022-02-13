#pragma once

#include "RScreenCapture.hpp"

#include <ScreenCapture.h>
#include <QString>
#include <QLabel>
#include <atomic>

namespace Scipper
{
	struct ImageData
	{
		ImageData(const std::shared_ptr<uchar[]>& pData, uint32_t width, uint32_t height) : p_ImageData(std::move(pData)), m_Width(width), m_Height(height) {}
		std::shared_ptr<uchar[]> p_ImageData = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};

	/**
	 * Screen class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Screen final : public QObject, public RScreenCapture
	{
		Q_OBJECT
			using ScreenCaptureConfig = std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager>;

	public:
		/**
		 * Constructor.
		 *
		 * @param name The name of the screen.
		 */
		Screen(QString name);

		/**
		 * Toggle the record boolean.
		 */
		void toggleRecord() { b_ShouldRecord = true; }

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
		 * @return The converted data.
		 */
		void convertRGBA(const SL::Screen_Capture::Image& image);

	private:
		QString m_Name;
		QImage m_Image;
		ScreenCaptureConfig p_Configuration = nullptr;
		std::atomic<bool> b_ShouldRecord = true;
		std::shared_ptr<ImageData> p_ImageData = nullptr;
	};
}