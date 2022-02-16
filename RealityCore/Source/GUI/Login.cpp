#include "Login.hpp"
#include "../../ui_Login.h"

#include <QMovie>
#include <QCryptographicHash>

namespace GUI
{
	Login::Login(QWidget* pParent)
		: QDialog(pParent, Qt::FramelessWindowHint)
		, m_pLogin(new Ui::Login())
	{
		// Setup the UI.
		m_pLogin->setupUi(this);

		// Create and assign the movie to the label.
		auto pMovie = new QMovie(":/Assets/2D/SplashScreen.gif");
		m_pLogin->movie->setMovie(pMovie);

		// Set the size of the movie and start playing.
		pMovie->setScaledSize(QSize(480, 270));
		pMovie->start();

		//setAttribute(Qt::WA_TranslucentBackground);
		setStyleSheet("background-color: black;");

		// Setup connections.
		connect(m_pLogin->signIn, &QPushButton::pressed, this, &Login::onSignIn);
		connect(m_pLogin->signUp, &QPushButton::pressed, this, &Login::onSignUp);
	}

	Login::~Login()
	{
		// Delete the allocated memory.
		delete m_pLogin;
	}

	QString Login::getUsername() const
	{
		return m_pLogin->username->text();
	}

	QByteArray Login::getPassword() const
	{
		// Hash and return the hashed bytes.
		return QCryptographicHash::hash(m_pLogin->password->text().toLocal8Bit(), QCryptographicHash::Sha3_512);
	}

	void Login::clearInput()
	{
		m_pLogin->username->clear();
		m_pLogin->password->clear();
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