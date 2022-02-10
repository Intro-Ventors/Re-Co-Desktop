#include "MainWindow.h"
#include "../../ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, p_MainWindow(new Ui::MainWindow)
{
	// Setup the UI.
	p_MainWindow->setupUi(this);
}

MainWindow::~MainWindow()
{
	// Deleted the allocated window.
	delete p_MainWindow;
}

