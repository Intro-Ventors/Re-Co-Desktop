#include "ApplicationGUI.hpp"

#include <QTimer>

namespace GUI
{
	ApplicationGUI::ApplicationGUI(int argc, char** argv, Scipper::Instance& instance)
		: m_Application(argc, argv)
		, m_Window(instance)
		, m_SystemTrayIcon(QIcon(":Assets/2D/Re-Co Logo.ico"))
	{
		// Show the splash screen.
		m_SplashScreen.show();

		// Connect the system tray activation handler.
		QObject::connect(&m_SystemTrayIcon, &QSystemTrayIcon::activated, this, &ApplicationGUI::onSystemTrayActivation);

		// Set the system tray icon tool tip.
		m_SystemTrayIcon.setToolTip("Reality Core");

		// Create the system tray icon context menu and set it.
		createContextMenu();
		m_SystemTrayIcon.setContextMenu(m_pContextMenu.get());

		// Show it to the user.
		m_SystemTrayIcon.show();

		// Create a timer to simulate loading. This is not needed if the application takes a longer time to load assets.
		// But this is added because the application loads fairly quickly. We wait for 5 seconds before closing it.
		using namespace std::chrono_literals;
		QTimer::singleShot(5s, [this]
			{
				// Show the main window.
				m_Window.showMaximized();

				// Finish the splash screen by passing the control to the main window.
				m_SplashScreen.finish(&m_Window);
			}
		);
	}

	int ApplicationGUI::run() const
	{
		return m_Application.exec();
	}

	void ApplicationGUI::createContextMenu()
	{
		// Create the pointer.
		m_pContextMenu = std::make_unique<QMenu>();

		// Add the menu options.
		m_pContextMenu->addAction(QIcon(":/Assets/2D/Exit.png"), "Exit", [this]
			{
				// Make the window a close-able widget.
				m_Window.toggleCloseable();

				// Close the main window.
				m_Window.close();
			}
		);
	}

	void ApplicationGUI::onSystemTrayActivation(QSystemTrayIcon::ActivationReason reason)
	{
		switch (reason)
		{
		case QSystemTrayIcon::Unknown:
			break;

		case QSystemTrayIcon::Context:
			break;

		case QSystemTrayIcon::DoubleClick:
			// If the window is not visible, maximize and show the window.
			if (m_Window.isHidden())
			{
				// Show the window.
				m_Window.showMaximized();

				// Refresh the screens to be displayed.
				m_Window.refreshScreens();
			}

			break;

		case QSystemTrayIcon::Trigger:
			break;

		case QSystemTrayIcon::MiddleClick:
			break;

		default:
			break;
		}
	}
}