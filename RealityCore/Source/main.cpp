#include "GUI/MainWindow.hpp"
#include "GUI/SplashScreen.hpp"
#include "GUI/Login.hpp"

#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[])
{
	// Setup the application.
	QApplication application(argc, argv);

	// Create the window instance.
	auto window = GUI::MainWindow();

	// Create the splash screen object.
	auto splashScreen = GUI::SplashScreen();

	// Show the splash screen.
	splashScreen.show();

	// Create a timer to simulate loading. This is not needed if the application takes a longer time to load assets.
	// But this is added because the application loads fairly quickly. We wait for 5 seconds before closing it.
	using namespace std::chrono_literals;
	QTimer::singleShot(5s, [&]
		{
			// Show the main window.
			window.show();

			// Finish the splash screen by passing the control to the main window.
			splashScreen.finish(&window);
		}
	);

	// Execute the application.
	return application.exec();
}
