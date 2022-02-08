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
		 * Refresh the screen titles.
		 */
		void refreshTitles();

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

		/**
		 * Get all the screen titles.
		 * 
		 * @return The title list.
		 */
		std::vector<std::string> getScreenTitles() const;

		/**
		 * Get all the screen titles.
		 *
		 * @return The title list.
		 */
		std::vector<std::string>& getScreenTitles();

	private:
		std::vector<Screen> m_Screens;
		std::vector<std::string> m_ScreenTitles;
	};
}