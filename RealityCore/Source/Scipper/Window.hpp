#pragma once

#include "FrameCapture.hpp"

namespace Scipper
{
	/**
	 * Window class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Window final : public FrameCapture
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param name The name of the screen.
		 */
		Window(QString name);

	private:
		/**
		 * Function to handle new frame.
		 *
		 * @param image The frame image.
		 * @param window The window in which the new frame is captured.
		 */
		void onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Window& window);
	};
}