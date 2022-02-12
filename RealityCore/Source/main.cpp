#include "GUI/MainWindow.h"
#include "GUI/SplashScreen.h"
#include "GUI/Login.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[])
{
	// Setup the application.
	QApplication application(argc, argv);

	// Create the window instance.
	GUI::MainWindow window = {};

	// Create the login dialog.
	auto pLogin = new GUI::Login();

	// Connect the finished signal to our slot.
	QObject::connect(pLogin, &QDialog::finished, [&window, pLogin](int result)
		{
			// Accepted means that the user has pressed sign in.
			if (result == QDialog::Accepted)
			{
				// Show the window to the user.
				window.show();
			}

			// Else we can just skip and close the application.
			delete pLogin;
		});

	// Show the login dialog.
	pLogin->show();

	// Execute the application.
	return application.exec();
}
