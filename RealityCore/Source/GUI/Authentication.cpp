#include "Authentication.hpp"
#include "../../ui_Authentication.h"

#include <qrcodegen.hpp>
#include <QCryptographicHash>
#include <random>

namespace GUI
{
	QString IPAndPortToString(QString IP, unsigned int port)
	{
		return IP + ":" + QString::number(port);
	}

	QByteArray GenerateOTP(unsigned char rootLength)
	{
		// Create the random engine to create the random sequence.
		std::default_random_engine randomEngine;

		// Create a random byte array.
		QByteArray byteArray;
		for (unsigned char i = 0; i < rootLength; i++)
			byteArray.append(static_cast<char>(randomEngine() % 128));

		// Hash the byte array and return the result as the OTP.
		return QCryptographicHash::hash(byteArray, QCryptographicHash::Algorithm::Sha1);
	}

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

		// Don't let the user to resize the window.
		setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	}

	Authentication::~Authentication()
	{
		// Delete the allocated memory.
		delete m_pAuthentication;

		// This is bad but we have to do this.
		delete this;
	}
}
