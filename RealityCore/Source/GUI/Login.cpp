#include "Login.h"
#include "../../ui_Login.h"

#include <QMovie>
#include <QCryptographicHash>

namespace GUI
{
	Login::Login(QWidget* pParent)
		: QDialog(pParent, Qt::FramelessWindowHint)
		, p_Login(new Ui::Login())
	{
		// Setup the UI.
		p_Login->setupUi(this);

		// Create and assign the movie to the label.
		auto pMovie = new QMovie(":/Assets/SplashScreen.gif");
		p_Login->movie->setMovie(pMovie);

		// Set the size of the movie and start playing.
		pMovie->setScaledSize(QSize(480, 270));
		pMovie->start();

		//setAttribute(Qt::WA_TranslucentBackground);
		setStyleSheet("background-color: black;");

		// Setup connections.
		connect(p_Login->signIn, &QPushButton::pressed, this, &Login::onSignIn);
		connect(p_Login->signUp, &QPushButton::pressed, this, &Login::onSignUp);
	}

	Login::~Login()
	{
		// Delete the allocated memory.
		delete p_Login;
	}

	QString Login::getUsername() const
	{
		return p_Login->username->text();
	}

	QByteArray Login::getPassword() const
	{
		// Hash and return the hashed bytes.
		return QCryptographicHash::hash(p_Login->password->text().toLocal8Bit(), QCryptographicHash::Sha3_512);
	}

	void Login::clearInput()
	{
		p_Login->username->clear();
		p_Login->password->clear();
	}

	void Login::onSignIn()
	{
		const auto username = getUsername();
		const auto password = getPassword();

		// Clear the user inputs.
		clearInput();

		// Whatever the log in logic.

		// Say that we accept the login.
		accept();
	}

	void Login::onSignUp()
	{
		// Clear the user inputs.
		clearInput();

		// Whatever the sign up logic.

		// Say that we rejected it.
		reject();
	}
}