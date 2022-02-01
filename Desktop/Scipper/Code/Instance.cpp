#include "Instance.hpp"

#include <ScreenCapture.h>

namespace Scipper
{
	Instance::Instance()
	{
		const auto monitors = SL::Screen_Capture::GetMonitors();
		const auto windows = SL::Screen_Capture::GetWindows();
	}

	std::vector<Screen> Instance::getScreens() const
	{
		return m_Screens;
	}

	std::vector<Screen>& Instance::getScreens()
	{
		return m_Screens;
	}
}