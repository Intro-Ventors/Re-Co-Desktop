#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Authentication; }
QT_END_NAMESPACE

namespace GUI
{
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

	private:
		Ui::Authentication* m_pAuthentication = nullptr;
	};
}