// Copyright (c) 2022 Intro-Ventors

#pragma once

#include "FrameCapture.hpp"

namespace Scipper
{
	/**
	 * Monitor class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Monitor final : public FrameCapture
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param name The name of the screen.
		 */
		Monitor(QString name);

	private:
		/**
		 * Function to handle new frame.
		 *
		 * @param image The frame image.
		 * @param monitor The monitor in which the new frame is captured.
		 */
		void onNewFrame(const SL::Screen_Capture::Image& image, const SL::Screen_Capture::Monitor& monitor);
	};
}