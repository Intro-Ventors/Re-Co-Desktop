#include <iostream>
#include "Instance.hpp"

int main()
{
	Scipper::Instance mInstance;
	auto const& screens = mInstance.getScreenTitles();
	return 0;
}