// Copyright (c) 2022 Intro-Ventors

#pragma once

#include "Window.hpp"
#include "Monitor.hpp"

#include <vector>
#include <QVector>

namespace Scipper
{
	/**
	 * Instance class.
	 * This class contains a single instance of the screen capturing API. You will only need one instance of it.
	 */
	class Instance final : public RScreenCapture
	{
	public:
		/**
		 * Default constructor.
		 */
		Instance() = default;

		/**
		 * Refresh the screen and monitor titles.
		 */
		void refreshTitles();

		/**
		 * Refresh the windows.
		 * This will refresh all the titles and recreate the windows vector.
		 *
		 * @param limit The window limit.
		 * @return The windows that were just created.
		 */
		std::vector<std::shared_ptr<Window>>& refreshWindows(int limit = 5);

		/**
		 * Refresh the monitors.
		 * This will refresh all the titles and recreate the monitors vector.
		 *
		 * @return The monitors that were just created.
		 */
		std::vector<std::shared_ptr<Monitor>>& refreshMonitors();

		/**
		 * Get the windows from the instance.
		 *
		 * @return The windows vector.
		 */
		std::vector<std::shared_ptr<Window>>& getWindows() { return m_Windows; }

		/**
		 * Get the monitors from the instance.
		 *
		 * @return The monitors vector.
		 */
		std::vector<std::shared_ptr<Monitor>>& getMonitors() { return m_Monitors; }

		/**
		 * Get all the window titles.
		 *
		 * @return The title list.
		 */
		QVector<QString> getWindowTitles() const { return m_WindowTitles; }

		/**
		 * Get all the window titles.
		 *
		 * @return The title list.
		 */
		QVector<QString>& getWindowTitles() { return m_WindowTitles; }

		/**
		 * Get all the monitor titles.
		 *
		 * @return The title list.
		 */
		QVector<QString> getMonitorTitles() const { return m_MonitorTitles; }

		/**
		 * Get all the monitor titles.
		 *
		 * @return The title list.
		 */
		QVector<QString>& getMonitorTitles() { return m_MonitorTitles; }

	private:
		/**
		 * Refresh the window titles.
		 */
		void refreshWindowTitles();

		/**
		 * Refresh the monitor titles.
		 */
		void refreshMonitorTitles();

	private:
		std::vector<std::shared_ptr<Window>> m_Windows;
		std::vector<std::shared_ptr<Monitor>> m_Monitors;
		QVector<QString> m_WindowTitles;
		QVector<QString> m_MonitorTitles;
	};
}