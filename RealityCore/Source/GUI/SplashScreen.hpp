// Copyright (c) 2022 Intro-Ventors

#pragma once

#include <QSplashScreen>
#include <QMovie>

namespace GUI
{
	/**
	 * Splash screen object.
	 * Splash screens are the windows that are shown to the user when the application is initializing itself.
	 */
	class SplashScreen : public QSplashScreen
	{
		Q_OBJECT

	public:
		/**
		 * Default constructor.
		 */
		SplashScreen();

		/**
		 * Finish the movie.
		 */
		void finishMovie();

	private slots:
		/**
		 * Function to handle the frame change signal.
		 *
		 * @param frameNumber The frame number in the movie.
		 */
		void onFrameChange(int frameNumber);

	private:
		QMovie m_Movie = QMovie(":/Assets/2D/SplashScreen.gif");
	};
}