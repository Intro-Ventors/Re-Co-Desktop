#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * Login class.
	 * This class contains the user login logic.
	 */
	class Login : public QWidget
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

	private:
		Ui::Login* p_Login = nullptr;
	};
}

