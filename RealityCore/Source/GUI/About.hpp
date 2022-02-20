#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class About; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * About object.
	 * This object contains the about section of the application.
	 */
	class About : public QWidget
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param pParent The parent object pointer. Default is nullptr.
		 */
		About(QWidget* pParent = nullptr);

		/**
		 * Default destructor.
		 */
		~About();

		/**
		 * Override the close event.
		 *
		 * @param pCloseEvent The close event pointer.
		 */
		void closeEvent(QCloseEvent* pCloseEvent) override;

	private:
		Ui::About* m_pAbout = nullptr;
	};
}