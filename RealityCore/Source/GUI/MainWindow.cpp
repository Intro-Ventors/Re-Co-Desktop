#include "MainWindow.hpp"
#include "../../ui_MainWindow.h"

#include "About.hpp"
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

		// Create the help menu and add them to the menu.
		QMenu* pMenu = new QMenu("Help", m_pMainWindow->menubar);
		m_pMainWindow->menubar->addMenu(pMenu);

		// Add the about action.
		pMenu->addAction("About", [this]
			{
				// Create the about window and show it to the user.
				auto pAbout = new About();
				pAbout->show();
			});

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
