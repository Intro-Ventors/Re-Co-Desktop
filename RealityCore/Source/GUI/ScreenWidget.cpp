#include "ScreenWidget.hpp"
#include "../../ui_Screen.h"

#include <QPainter>
#include <QPaintEvent>

namespace GUI
{
	ScreenWidget::ScreenWidget(QWidget* pParent)
		: QWidget(pParent)
		, m_pScreen(new Ui::Window())
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
			auto image = QImage(reinterpret_cast<const uint8_t*>(m_pImage->p_ImageData.data()), m_pImage->m_Width, m_pImage->m_Height, QImage::Format::Format_RGBA8888);

			// Scale it down a little.
			image = image.scaled(QSize(854, 480));

			// Set the image as a pixmap.
			m_pScreen->frame->setPixmap(QPixmap::fromImage(image));

			// Set the delta time.
			if (m_pImage->m_DeltaTime > 0)
				m_pScreen->time->setText("Delta time: " + QString::number(m_pImage->m_DeltaTime) + " ms (" + QString::number(1000 / m_pImage->m_DeltaTime) + " FPS)");
		}

		// Paint everything with the default painting.
		QWidget::paintEvent(pEvent);

		// Toggle the record so the screen capturing API can record a new image.
		m_pFrameCapture->toggleRecord();
	}

	void ScreenWidget::setFrameCapture(std::shared_ptr<Scipper::FrameCapture> pFrameCapture)
	{
		m_pFrameCapture = pFrameCapture;

		// Set the connection.
		connect(m_pFrameCapture.get(), &Scipper::FrameCapture::newFrame, this, &ScreenWidget::onNewFrame);
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