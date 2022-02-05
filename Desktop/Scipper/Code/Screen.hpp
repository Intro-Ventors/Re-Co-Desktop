#pragma once

#include "RScreenCapture.hpp"
#include <string>

namespace Scipper
{
	/**
	 * Screen class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Screen final : public RScreenCapture
	{
	public:
		/**
		 * Constructor.
		 * 
		 * @param name The name of the screen.
		 */
		Screen(std::string_view name);

	private:
		std::string_view m_Name;
	};
}