#pragma once

#include "RScreenCapture.hpp"

#include <ScreenCapture.h>

#include <QObject>
#include <QString>

namespace Scipper
{
	/**
	 * Frame capture object.
	 * This class is the base class for both window and monitor capture objects.
	 */
	class FrameCapture : public QObject, public RScreenCapture
	{
		Q_OBJECT

	public:
		using CaptureConfig = std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager>;
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;

		/**
		 * Converting constructor.
		 *
		 * @param name The name of the frame.
		 */
		FrameCapture(QString name);

		/**
		 * Toggle the record boolean.
		 */
		void toggleRecord() { m_bShouldRecord = true; }

		/**
		 * Get the name of the frame.
		 *
		 * @return The QString object.
		 */
		const QString getName() const { return m_Name; }

	signals:
		/**
		 * Signal indicating that a new frame was added.
		 *
		 * @param image The new image.
		 */
		void newFrame(std::shared_ptr<ImageData> image);

	protected:
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

	protected:
		QString m_Name;
		CaptureConfig m_pConfiguration = nullptr;
		std::atomic<bool> m_bShouldRecord = true;
		std::shared_ptr<ImageData> m_pImageData = nullptr;
		TimePoint m_TimePoint;
	};
}