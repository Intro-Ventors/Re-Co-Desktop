#include "About.hpp"
#include "../../ui_About.h"

namespace GUI
{
	About::About(QWidget* pParent)
		: QWidget(pParent)
		, m_pAbout(new Ui::About())
	{
		// Setup the UI.
		m_pAbout->setupUi(this);
	}

	About::~About()
	{
		// Delete the allocated pointer.
		delete m_pAbout;

		// Yeah this is not the best thing to do but you can do this because there is no other way.
		delete this;
	}
}
