#include "Login.h"
#include "../../ui_Login.h"

namespace GUI
{
	Login::Login(QWidget* pParent)
		: QWidget(pParent)
		, p_Login(new Ui::Login())
	{
		// Setup the UI.
		p_Login->setupUi(this);
	}

	Login::~Login()
	{
		delete p_Login;
	}
}