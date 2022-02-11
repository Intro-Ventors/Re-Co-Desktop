#include "MainWindow.h"
#include "../../ui_MainWindow.h"

#include "About.h"

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
	}

	MainWindow::~MainWindow()
	{
		// Deleted the allocated window.
		delete p_MainWindow;
	}
}
