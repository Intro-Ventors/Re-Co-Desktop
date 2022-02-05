#include <iostream>
#include "Instance.hpp"

int main()
{
	Scipper::Instance mInstance;
	auto const& screens = mInstance.getScreens();
	return 0;
}