#pragma once

#include <thread>
#include "DesktopDuplication.hpp"
#include <QObject>

namespace Scipper
{
	/**
	 * Duplication image data struct.
	 * This struct contains the image information which are prepared to be rendered by Qt.
	 */
	struct DuplicationImage
	{
		DuplicationImage() = default;
		DuplicationImage(std::vector<RGBA8>&& image, uint32_t width, uint32_t height) : m_Image(image), m_Width(width), m_Height(height) {}

		std::vector<RGBA8> m_Image;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};

	/**
	 * Duplication thread.
	 * This object acts as a single duplication thread and houses the monitor capturing mechanism.
	 */
	class DuplicationThread : public QObject
	{
		Q_OBJECT

	public:
		/**
		 * Default constructor.
		 */
		DuplicationThread();

		/**
		 * Terminate the thread.
		 */
		void terminate() { m_bShouldRun = false; }

	signals:
		/**
		 * Tick signal.
		 * This signal is emitted once every tick (iteration).
		 * 
		 * @param delta The time delta in nanoseconds.
		 */
		void tick(std::chrono::nanoseconds delta);

		/**
		 * Image signal.
		 * This signal is emitted once the incoming image is ready to be rendered by Qt.
		 * 
		 * @param image The image containing the monitor data.
		 */
		void image(const DuplicationImage& image);

	private:
		std::jthread m_Thread;
		std::unique_ptr<DesktopDuplication> m_pDesktopDuplication = nullptr;

		std::atomic<bool> m_bShouldRun = true;
	};
}