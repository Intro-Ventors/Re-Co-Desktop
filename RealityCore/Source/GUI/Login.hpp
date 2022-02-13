#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * Login class.
	 * This class contains the user login logic.
	 */
	class Login : public QDialog
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param pParent The parent widget pointer. Default is nullptr.
		 */
		Login(QWidget* pParent = nullptr);

		/**
		 * Default destructor.
		 */
		~Login();

		/**
		 * Get the username from the user.
		 *
		 * @return The QString object.
		 */
		QString getUsername() const;

		/**
		 * Get the password from the user.
		 * This will return the hashed output. The hashing algorithm is SHA3-512.
		 *
		 * @return The QByteArray object
		 */
		QByteArray getPassword() const;

	private:
		/**
		 * Clear the user inputs.
		 * This is needed as soon as the user clicks on a button to make sure that the user data are kept safe.
		 */
		void clearInput();

	private slots:
		/**
		 * Slot handling sign in button press.
		 */
		void onSignIn();

		/**
		 * Slot handling sign up button press.
		 */
		void onSignUp();

	private:
		Ui::Login* p_Login = nullptr;
	};
}

