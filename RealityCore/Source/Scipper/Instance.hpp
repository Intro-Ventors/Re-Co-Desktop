#pragma once

#include "Screen.hpp"
#include <vector>
#include <QVector>

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
		Instance() = default;

		/**
		 * Refresh the screen titles.
		 */
		void refreshTitles();

		/**
		 * Refresh the screens.
		 * This will refresh all the titles and recreate the screens vector.
		 * 
		 * @param limit The screen limit.
		 * @return The screens that were just created.
		 */
		std::vector<std::shared_ptr<Screen>>& refreshScreens(int limit = 5);

		/**
		 * Get the screens from the instance.
		 *
		 * @return The screens vector.
		 */
		std::vector<std::shared_ptr<Screen>>& getScreens() { return m_Screens; }

		/**
		 * Get all the screen titles.
		 *
		 * @return The title list.
		 */
		QVector<QString> getScreenTitles() const { return m_ScreenTitles; }

		/**
		 * Get all the screen titles.
		 *
		 * @return The title list.
		 */
		QVector<QString>& getScreenTitles() { return m_ScreenTitles; }

	private:
		std::vector<std::shared_ptr<Screen>> m_Screens;
		QVector<QString> m_ScreenTitles;
	};
}