#include "MainWindow.hpp"
#include "../../ui_MainWindow.h"

#include "About.hpp"
#include "Authentication.hpp"
#include "ScreenWidget.hpp"

namespace GUI
{
	MainWindow::MainWindow(QWidget* pParent)
		: QMainWindow(pParent)
		, m_pMainWindow(new Ui::MainWindow())
		, m_pScrollArea(new QScrollArea(this))
	{
		// Setup the UI.
		m_pMainWindow->setupUi(this);

		// Create the about menu.
		setupAboutMenu();

		// Create the login menu.
		setupLoginMenu();

		// Set the window icon.
		setWindowIcon(QIcon(":Assets/2D/Re-Co Logo.ico"));

		// Add the scroll area widget.
		//p_MainWindow->verticalLayout->addWidget(p_ScrollArea);
		setCentralWidget(m_pScrollArea);

		// Setup the screens.
		setupWindows();
	}

	MainWindow::~MainWindow()
	{
		// Deleted the allocated window.
		delete m_pMainWindow;
	}

	void MainWindow::setupAboutMenu()
	{
		// Create the help menu and add them to the menu.
		QMenu* pMenu = new QMenu("Help", m_pMainWindow->menubar);
		m_pMainWindow->menubar->addMenu(pMenu);

		// Add the about action.
		pMenu->addAction("About", []
			{
				// Create the widget and show it to the user.
				auto pWidget = new About();
				pWidget->show();
			});
	}

	void MainWindow::setupLoginMenu()
	{
		// Create the help menu and add them to the menu.
		QMenu* pMenu = new QMenu("Login", m_pMainWindow->menubar);
		m_pMainWindow->menubar->addMenu(pMenu);

		// Add the about action.
		pMenu->addAction("Authenticate", []
			{
				// Generate the OTP. This is here for debugging purposes.
				const auto password = GenerateOTP();

				// Create the widget and show it to the user.
				// This QR code will contain the IPv4 address to where the device should connect to. It contains the IP address, port and 
				// the authentication password. The format will look like the following.
				// 127.0.0.1:8080#OTP
				auto pWidget = new Authentication(IPAndPortToString("127.0.0.1", 8080) + "#" + password.toBase64());
				pWidget->show();
			});
	}

	void MainWindow::setupWindows()
	{
		QVBoxLayout* pBoxLayout = new QVBoxLayout(m_pScrollArea);

		//auto& windows = m_Instance.refreshWindows();
		//for (const auto& window : windows)
		//{
		//	auto pScreenWidget = new ScreenWidget(this);
		//	pScreenWidget->setFrameCapture(window);
		//	pBoxLayout->addWidget(pScreenWidget);
		//}

		auto& monitors = m_Instance.refreshMonitors();
		for (const auto& monitor : monitors)
		{
			auto pScreenWidget = new ScreenWidget(this);
			pScreenWidget->setFrameCapture(monitor);
			pBoxLayout->addWidget(pScreenWidget);
		}
	}
}
