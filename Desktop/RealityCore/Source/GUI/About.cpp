#include "About.h"
#include "../../ui_About.h"

namespace GUI
{
	About::About(QWidget* pParent)
		: QWidget(pParent)
		, p_About(new Ui::About())
	{
		// Setup the UI.
		p_About->setupUi(this);
	}

	About::~About()
	{
		// Delete the allocated pointer.
		delete p_About;
	}
}
