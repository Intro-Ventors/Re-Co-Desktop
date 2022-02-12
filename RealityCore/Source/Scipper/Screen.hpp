#pragma once

#include "RScreenCapture.hpp"

#include <ScreenCapture.h>
#include <QString>


namespace Scipper
{
	/**
	 * Screen class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Screen final : public RScreenCapture
	{
		using ScreenCaptureConfig = std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager>;

	public:
		/**
		 * Constructor.
		 * 
		 * @param name The name of the screen.
		 */
		Screen(QString name);

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
		QString m_Name;
		ScreenCaptureConfig p_Configuration = nullptr;
	};
}