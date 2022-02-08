#include "Instance.hpp"

#include <ScreenCapture.h>

namespace Scipper
{
	Instance::Instance()
	{
		const auto windows = SL::Screen_Capture::GetWindows();

		for (auto const& window : windows)
			m_Screens.emplace_back(std::string_view(window.Name));
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