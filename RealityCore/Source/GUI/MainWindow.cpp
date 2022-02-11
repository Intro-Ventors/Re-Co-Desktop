#include "MainWindow.h"
#include "../../ui_MainWindow.h"

#include "Login.h"

namespace GUI
{
	MainWindow::MainWindow(QWidget* pParent)
		: QMainWindow(pParent)
		, p_MainWindow(new Ui::MainWindow)
	{
		// Setup the UI.
		p_MainWindow->setupUi(this);

		QMenu* pMenu = new QMenu("Help", p_MainWindow->menubar);
		pMenu->addAction("About", [this]
			{
				p_MainWindow->gridLayout->addWidget(new Login(this));
			});

		auto pLogin = new Login();
		pLogin->show();
		p_MainWindow->menubar->addMenu(pMenu);
	}

	MainWindow::~MainWindow()
	{
		// Deleted the allocated window.
		delete p_MainWindow;
	}
}
