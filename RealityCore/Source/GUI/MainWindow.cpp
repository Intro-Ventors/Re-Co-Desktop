#include "MainWindow.hpp"
#include "../../ui_MainWindow.h"

#include "About.hpp"
#include "ScreenWidget.hpp"

namespace GUI
{
	MainWindow::MainWindow(QWidget* pParent)
		: QMainWindow(pParent)
		, p_MainWindow(new Ui::MainWindow)
	{
		// Setup the UI.
		p_MainWindow->setupUi(this);

		// Create the help menu and add them to the menu.
		QMenu* pMenu = new QMenu("Help", p_MainWindow->menubar);
		p_MainWindow->menubar->addMenu(pMenu);

		// Add the about action.
		pMenu->addAction("About", [this]
			{
				// Create the about window and show it to the user.
				auto pAbout = new About();
				pAbout->show();
			});

		// Set the window icon.
		setWindowIcon(QIcon(":Assets/2D/Re-Co Logo.ico"));

		// Setup the screens.
		setupScreens();
	}

	MainWindow::~MainWindow()
	{
		// Deleted the allocated window.
		delete p_MainWindow;
	}

	void MainWindow::setupScreens()
	{
		auto& screens = m_Instance.refreshScreens();

		for (const auto& screen : screens)
		{
			auto pWidget = new ScreenWidget(this);
			pWidget->setScreen(screen);
			p_MainWindow->verticalLayout->addWidget(pWidget);
		}
	}
}
