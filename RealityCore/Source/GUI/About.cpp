// Copyright (c) 2022 Intro-Ventors

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

		// Set the logo.
		m_pAbout->logo->setPixmap(QPixmap(":Assets/2D/Re-Co Logo.png"));

		// Set the fixed window size.
		setFixedSize(QSize(700, 700));
	}

	About::~About()
	{
		// Delete the allocated pointer.
		delete m_pAbout;
	}

	void About::closeEvent(QCloseEvent* pCloseEvent)
	{
		// Call the default widget close event.
		QWidget::closeEvent(pCloseEvent);

		// Yeah this is not the best thing to do but you can do this because there is no other way.
		delete this;
	}
}
