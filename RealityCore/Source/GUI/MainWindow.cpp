#include "MainWindow.hpp"
#include "../../ui_MainWindow.h"

#include "About.hpp"
#include "ScreenWidget.hpp"

namespace GUI
{
	MainWindow::MainWindow(QWidget* pParent)
		: QMainWindow(pParent)
		, p_MainWindow(new Ui::MainWindow())
		, p_ScrollArea(new QScrollArea(this))
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

		// Add the scroll area widget.
		//p_MainWindow->verticalLayout->addWidget(p_ScrollArea);
		setCentralWidget(p_ScrollArea);

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
		auto& screens = m_Instance.refreshScreens(1);

		QVBoxLayout* pBoxLayout = new QVBoxLayout(p_ScrollArea);

		for (const auto& screen : screens)
		{
			auto pScreenWidget = new ScreenWidget(this);
			pScreenWidget->setScreen(screen);
			pBoxLayout->addWidget(pScreenWidget);
		}

		//p_ScrollArea->setWidget(pWindow);
	}
}
