#pragma once

#include "MainWindow.hpp"
#include "SplashScreen.hpp"
#include "Login.hpp"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>

namespace GUI
{
	/**
	 * Application GUI class.
	 * This class contains the main GUI elements of Re-Co.
	 */
	class ApplicationGUI : public QObject
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param argc The command line argument count.
		 * @param argv The command line arguments.
		 * @param instance The scipper instance.
		 */
		ApplicationGUI(int argc, char** argv, Scipper::Instance& instance);

		/**
		 * Run the application.
		 *
		 * @return The exit code.
		 */
		int run() const;

	private slots:
		/**
		 * Slot to handle the system tray icon activation.
		 *
		 * @param reason The activation reason.
		 */
		void onSystemTrayActivation(QSystemTrayIcon::ActivationReason reason);

	private:
		/**
		 * Create the context menu for the system tray icon.
		 */
		void createContextMenu();

	private:
		QApplication m_Application;

		MainWindow m_Window;
		SplashScreen m_SplashScreen;
		QSystemTrayIcon m_SystemTrayIcon;

		std::unique_ptr<QMenu> m_pContextMenu = nullptr;
	};
}