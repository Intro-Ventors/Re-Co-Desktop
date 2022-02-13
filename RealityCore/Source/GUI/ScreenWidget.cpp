#include "ScreenWidget.hpp"
#include "../../ui_Screen.h"

#include <QPainter>
#include <QPaintEvent>

namespace GUI
{
	ScreenWidget::ScreenWidget(QWidget* pParent)
		: QWidget(pParent)
		, p_Screen(new Ui::Screen())
	{
		// Set the UI pointer as this.
		p_Screen->setupUi(this);
	}

	ScreenWidget::~ScreenWidget()
	{
		// Delete the allocated memory.
		delete p_Screen;
	}

	void ScreenWidget::paintEvent(QPaintEvent* pEvent)
	{
		// If the image is present, lets set it to the label.
		if (m_Image)
		{
			// Create the image using the image data.
			auto image = QImage(m_Image->p_ImageData.get(), m_Image->m_Width, m_Image->m_Height, QImage::Format::Format_RGBA8888);

			// Scale it down a little.
			image.scaled(QSize(854, 480));

			// Set the image as a pixmap.
			p_Screen->frame->setPixmap(QPixmap::fromImage(image));
		}
		QWidget::paintEvent(pEvent);

		// Toggle the record so the screen capturing API can record a new image.
		p_ScipperScreen->toggleRecord();
	}

	void ScreenWidget::setScreen(std::shared_ptr<Scipper::Screen> pScreen)
	{
		p_ScipperScreen = pScreen;

		// Set the connection.
		connect(p_ScipperScreen.get(), &Scipper::Screen::newFrame, this, &ScreenWidget::onNewFrame);
	}

	QLabel* ScreenWidget::getLabel() const
	{
		return p_Screen->frame;
	}

	void ScreenWidget::onNewFrame(std::shared_ptr<Scipper::ImageData> image)
	{
		m_Image = image;
	}
}