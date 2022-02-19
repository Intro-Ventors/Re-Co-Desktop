#include "Authentication.hpp"
#include "../../ui_Authentication.h"

#include <qrcodegen.hpp>

namespace GUI
{
	Authentication::Authentication(QString message, QWidget* pParent)
		: QWidget(pParent)
		, m_pAuthentication(new Ui::Authentication())
	{
		// Setup the UI controller.
		m_pAuthentication->setupUi(this);

		// Encode the text in the QR code.
		const qrcodegen::QrCode code = qrcodegen::QrCode::encodeText(message.toUtf8().data(), qrcodegen::QrCode::Ecc::MEDIUM);

		// Get the code size.
		qint32 codeSize = code.getSize();

		// Create the image to fit the QR code.
		QImage image(codeSize, codeSize, QImage::Format_RGB32);

		// Setup the pixels.
		constexpr QRgb black = qRgb(0, 0, 0);
		constexpr QRgb white = qRgb(255, 255, 255);

		// Create the image.
		for (int y = 0; y < codeSize; y++)
		{
			for (int x = 0; x < codeSize; x++)
			{
				image.setPixel(x, y, code.getModule(x, y) ? black : white);
			}
		}

		// Now set the image as a pixmap to the label.
		m_pAuthentication->image->setPixmap(QPixmap::fromImage(image.scaled(256, 256)));
	}

	Authentication::~Authentication()
	{
		// Delete the allocated memory.
		delete m_pAuthentication;

		// This is bad but we have to do this.
		delete this;
	}
}
