#include "GUI/ApplicationGUI.hpp"

int main(int argc, char* argv[])
{
	// Create the scipper instance.
	auto instance = Scipper::Instance();

	// Create the application GUI.
	auto applicationGUI = GUI::ApplicationGUI(argc, argv, instance);

	// Run the GUI.
	return applicationGUI.run();
}
