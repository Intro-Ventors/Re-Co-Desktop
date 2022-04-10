// Copyright (c) 2022 Intro-Ventors

#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Authentication; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * Convert the IP address and the port number to a string.
	 *
	 * @param IP The IP address.
	 * @param port The port number.
	 * @return The converted string.
	 */
	QString IPAndPortToString(QString IP, unsigned int port);

	/**
	 * Generate an one time password.
	 *
	 * @param rootLength The length of the random sequence from which the password is generated from. This has no effect on the output length.
	 * @return The byte array.
	 */
	QByteArray GenerateOTP(unsigned char rootLength = 8);

	/**
	 * Authentication class.
	 * This class is the controller for the authentication form, and is used to generate the QR code required for authentication.
	 */
	class Authentication : public QWidget
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param message The message that needs to be sent using the authentication QR code.
		 * @param pParent The parent widget pointer.
		 */
		Authentication(QString message, QWidget* pParent = nullptr);

		/**
		 * Default destructor.
		 */
		~Authentication();

		/**
		 * Override the close event.
		 *
		 * @param pCloseEvent The close event pointer.
		 */
		void closeEvent(QCloseEvent* pCloseEvent) override;

	signals:
		/**
		 * Authenticated signal.
		 * This signal is emitted once a user has been authenticated with the server.
		 */
		void authenticated();

	private:
		Ui::Authentication* m_pAuthentication = nullptr;
	};
}