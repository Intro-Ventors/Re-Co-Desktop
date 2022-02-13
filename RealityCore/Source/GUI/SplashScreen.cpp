#include "SplashScreen.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QApplication>

namespace GUI
{
	SplashScreen::SplashScreen()
	{
		// Connect the on frame change slot to the frame changed signal. 
		connect(&m_Movie, &QMovie::frameChanged, this, &SplashScreen::onFrameChange);

		// Set a smaller size than the original high resolution gif.
		m_Movie.setScaledSize(QSize(480, 270));

		// Start the animation.
		m_Movie.start();
	}

	void SplashScreen::finishMovie()
	{
		m_Movie.stop();
	}

	void SplashScreen::onFrameChange(int frameNumber)
	{
		// Set the variable as unused.
		Q_UNUSED(frameNumber);

		// Get the current pixmap. 
		const auto pixmap = m_Movie.currentPixmap();

		// Set the pixmap and mask.
		setPixmap(pixmap);
		setMask(pixmap.mask());
	}
}