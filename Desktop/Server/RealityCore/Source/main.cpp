#include "GUI/MainWindow.h"
#include "GUI/SplashScreen.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[])
{
	// Setup the application.
	QApplication application(argc, argv);

	// Create the splash screen object while we initialize the other components.
	SplashScreen splashScreen = {};
	splashScreen.show();

	// Create the window instance.
	MainWindow window = {};

	// Wait till the window initializes.
	QTimer::singleShot(5000, [&window, &splashScreen]
		{
			// Show the window to the user.
			window.show();
	
			// Finish the movie and transfer the control over to the window.
			splashScreen.finishMovie();
			splashScreen.finish(&window);
		}
	);

	// Execute the application.
	return application.exec();
}
