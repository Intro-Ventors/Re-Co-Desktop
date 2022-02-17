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

		//connect(&m_DuplicationThread, &Scipper::DuplicationThread::tick, this, &ScreenWidget::onTick);
		//connect(&m_DuplicationThread, &Scipper::DuplicationThread::image, this, &ScreenWidget::onImage);
	}

	ScreenWidget::~ScreenWidget()
	{
		// Delete the allocated memory.
		delete m_pScreen;

		//m_DuplicationThread.terminate();
	}

	void ScreenWidget::paintEvent(QPaintEvent* pEvent)
	{
		//// If the image is present, lets set it to the label.
		//if (true)
		//{
		//	// Create the image using the image data.
		//	auto image = QImage(reinterpret_cast<const uint8_t*>(m_DuplicationImage.m_Image.data()), m_DuplicationImage.m_Width, m_DuplicationImage.m_Height, QImage::Format::Format_RGBA8888);
		//
		//	// Set the image as a pixmap.
		//	m_pScreen->frame->setPixmap(QPixmap::fromImage(image.scaled(QSize(854, 480))));
		//
		//	// Set the delta time.
		//	m_pScreen->time->setText("Delta time: " + QString::number(m_Delta.load().count()) + " ns (" + QString::number(1000 / std::chrono::duration_cast<std::chrono::milliseconds>(m_Delta.load()).count()) + " FPS)");
		//}
		//
		//// Paint everything with the default painting.
		//QWidget::paintEvent(pEvent);
		//
		//// Toggle the record so the screen capturing API can record a new image.
		////m_pScipperScreen->toggleRecord();
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

	void ScreenWidget::onTick(std::chrono::nanoseconds delta)
	{
		m_Delta = delta;
	}

	void ScreenWidget::onImage(const Scipper::DuplicationImage& image)
	{
		m_DuplicationImage = std::move(image);
	}

	void ScreenWidget::onNewFrame(std::shared_ptr<Scipper::ImageData> image)
	{
		m_pImage = image;
	}
}