#pragma once

#include "Screen.hpp"
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
		 * @return The screens that were just created.
		 */
		QVector<Screen>& refreshScreens();

		/**
		 * Get the screens from the instance.
		 *
		 * @return The screens vector.
		 */
		QVector<Screen> getScreens() const { return m_Screens; }

		/**
		 * Get the screens from the instance.
		 *
		 * @return The screens vector.
		 */
		QVector<Screen>& getScreens() { return m_Screens; }

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
		QVector<Screen> m_Screens;
		QVector<QString> m_ScreenTitles;
	};
}