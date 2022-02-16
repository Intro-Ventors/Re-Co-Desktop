#include "ScreenWidget.hpp"
#include "../../ui_Screen.h"

#include <QPainter>
#include <QPaintEvent>

namespace GUI
{
	ScreenWidget::ScreenWidget(QWidget* pParent)
		: QWidget(pParent)
		, m_pScreen(new Ui::Screen())
	{
		// Set the UI pointer as this.
		m_pScreen->setupUi(this);
	}

	ScreenWidget::~ScreenWidget()
	{
		// Delete the allocated memory.
		delete m_pScreen;
	}

	void ScreenWidget::paintEvent(QPaintEvent* pEvent)
	{
		// If the image is present, lets set it to the label.
		if (m_pImage)
		{
			// Create the image using the image data.
			auto image = QImage(m_pImage->p_ImageData.get(), m_pImage->m_Width, m_pImage->m_Height, QImage::Format::Format_RGBA8888);

			// Set the image as a pixmap.
			m_pScreen->frame->setPixmap(QPixmap::fromImage(image.scaled(QSize(854, 480))));

			// Set the delta time.
			m_pScreen->time->setText("Delta time: " + QString::number(m_pImage->m_DeltaTime) + " ms (" + QString::number(1000 / m_pImage->m_DeltaTime) + " FPS)");
		}

		// Paint everything with the default painting.
		QWidget::paintEvent(pEvent);

		// Toggle the record so the screen capturing API can record a new image.
		m_pScipperScreen->toggleRecord();
	}

	void ScreenWidget::setScreen(std::shared_ptr<Scipper::Screen> pScreen)
	{
		m_pScipperScreen = pScreen;

		// Set the connection.
		connect(m_pScipperScreen.get(), &Scipper::Screen::newFrame, this, &ScreenWidget::onNewFrame);
	}

	QLabel* ScreenWidget::getLabel() const
	{
		return m_pScreen->frame;
	}

	void ScreenWidget::onNewFrame(std::shared_ptr<Scipper::ImageData> image)
	{
		m_pImage = image;
	}
}