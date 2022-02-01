#pragma once

#include "Screen.hpp"
#include <vector>

namespace Scipper
{
	/**
	 * Instance class.
	 * This class contains a single instance of the screen capturing API. You will only need one instance of it.
	 */
	class Instance final : public RScreenCapture
	{
	public:
		/**
		 * Default constructor.
		 */
		Instance();

		/**
		 * Get the screens from the instance.
		 * 
		 * @return The screens vector.
		 */
		std::vector<Screen> getScreens() const;

		/**
		 * Get the screens from the instance.
		 *
		 * @return The screens vector.
		 */
		std::vector<Screen>& getScreens();

	private:
		std::vector<Screen> m_Screens;
	};
}