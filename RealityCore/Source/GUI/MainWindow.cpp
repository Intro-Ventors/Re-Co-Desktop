// Copyright (c) 2022 Intro-Ventors

#include "MainWindow.hpp"
#include "../../ui_MainWindow.h"

#include "About.hpp"
#include "Authentication.hpp"

#include <QKeySequence>
#include <QCloseEvent>

namespace GUI
{
	MainWindow::MainWindow(Scipper::Instance& instance, QWidget* pParent)
		: QMainWindow(pParent)
		, m_pMainWindow(new Ui::MainWindow())
		, m_pScrollArea(new QScrollArea(this))
		, m_Instance(instance)
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
		setCentralWidget(m_pScrollArea);

		// Setup the screens.
		setupWindows();
	}

	MainWindow::~MainWindow()
	{
		// Deleted the allocated memory.
		delete m_pBoxLayout;
		delete m_pMainWindow;
	}

	void MainWindow::closeEvent(QCloseEvent* pCloseEvent)
	{
		// Just hide this widget if not close-able.
		if (m_bCloseable)
			QMainWindow::closeEvent(pCloseEvent);

		// Fully close if we can.
		else
		{
			// Remove the screen widgets from the layout.
			for (const auto& pWidget : m_ScreenWidgets)
				m_pBoxLayout->removeWidget(pWidget.get());

			// Clear them from the array.
			m_ScreenWidgets.clear();

			// Hide the window.
			hide();

			// Ignore the close event.
			pCloseEvent->ignore();
		}
	}

	void MainWindow::refreshScreens()
	{
		// Get the monitors.
		const auto& monitors = m_Instance.getMonitors();

		// Iterate over them and add them the layout.
		for (const auto& monitor : monitors)
		{
			// Create the widget.
			auto pScreenWidget = std::make_shared<ScreenWidget>(this);

			// Set the frame capture.
			pScreenWidget->setFrameCapture(monitor);

			// Add them to the box layout.
			m_pBoxLayout->addWidget(pScreenWidget.get());

			// Add them to the local vector.
			m_ScreenWidgets.emplace_back(std::move(pScreenWidget));
		}
	}

	void MainWindow::setupAboutMenu()
	{
		// Create the help menu and add them to the menu.
		auto pMenu = new QMenu("Help", m_pMainWindow->menubar);
		m_pMainWindow->menubar->addMenu(pMenu);

		// Add the about action.
		pMenu->addAction(QIcon(":/Assets/2D/About.png"), "About", [this]
			{
				// Create the widget and show it to the user.
				auto pWidget = new About();
				pWidget->show();

				// Connect the widget's destroyed signal to the lambda which will show this window maximized if hidden.
				connect(pWidget, &About::destroyed, [this](QObject*) 
					{
						if (isHidden())
						{
							showMaximized();
							refreshScreens();
						}
					}
				);
			},
			QKeySequence("Ctrl+a"));
	}

	void MainWindow::setupLoginMenu()
	{
		// Create the help menu and add them to the menu.
		auto pMenu = new QMenu("Login", m_pMainWindow->menubar);
		m_pMainWindow->menubar->addMenu(pMenu);

		// Add the about action.
		pMenu->addAction(QIcon(":/Assets/2D/Authenticate.png"), "Authenticate", [this]
			{
				// Generate the OTP. This is here for debugging purposes.
				const auto password = GenerateOTP();

				// Create the widget and show it to the user.
				// This QR code will contain the IPv4 address to where the device should connect to. It contains the IP address, port and 
				// the authentication password. The format will look like the following.
				// 127.0.0.1:8080#OTP
				auto pWidget = new Authentication(IPAndPortToString("127.0.0.1", 8080) + "#" + password.toBase64());
				pWidget->show();

				// Connect the widget's destroyed signal to the lambda which will show this window maximized if hidden.
				connect(pWidget, &About::destroyed, [this](QObject*)
					{
						if (isHidden())
						{
							showMaximized();
							refreshScreens();
						}
					}
				);
			},
			QKeySequence("Ctrl+l"));
	}

	void MainWindow::setupWindows()
	{
		m_pBoxLayout = new QVBoxLayout(m_pScrollArea);

		// Refresh the monitors and get the vector.
		const auto& monitors = m_Instance.refreshMonitors();

		// Iterate over them and add them the layout.
		for (const auto& monitor : monitors)
		{
			// Create the widget.
			auto pScreenWidget = std::make_shared<ScreenWidget>(this);

			// Set the frame capture.
			pScreenWidget->setFrameCapture(monitor);

			// Add them to the box layout.
			m_pBoxLayout->addWidget(pScreenWidget.get());

			// Add them to the local vector.
			m_ScreenWidgets.emplace_back(std::move(pScreenWidget));
		}
	}
}
