#pragma once

#include <thread>
#include "DesktopDuplication.hpp"
#include <QObject>

namespace Scipper
{
	struct DuplicationImage
	{
		DuplicationImage() = default;
		DuplicationImage(std::vector<RGBA8>&& image, uint32_t width, uint32_t height) : m_Image(image), m_Width(width), m_Height(height) {}
		DuplicationImage(const DuplicationImage&) = default;
		DuplicationImage(DuplicationImage&&) noexcept = default;

		DuplicationImage& operator=(const DuplicationImage&) = default;
		DuplicationImage& operator=(DuplicationImage&&) noexcept = default;

		std::vector<RGBA8> m_Image;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};

	class DuplicationThread : public QObject
	{
		Q_OBJECT

	public:
		DuplicationThread();

		void terminate() { m_bShouldRun = false; }

	signals:
		void tick(std::chrono::nanoseconds delta);
		void image(const DuplicationImage& image);

	private:
		std::jthread m_Thread;
		std::unique_ptr<DesktopDuplication> m_pDesktopDuplication = nullptr;

		std::atomic<bool> m_bShouldRun = true;
	};
}