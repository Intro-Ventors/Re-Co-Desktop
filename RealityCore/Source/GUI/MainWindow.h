#pragma once

#include <QMainWindow>

#include "../Scipper/Instance.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * Main window class.
	 * This class contains the main window of the entire desktop application.
	 */
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param pParent The parent object. Default is nullptr.
		 */
		MainWindow(QWidget* pParent = nullptr);

		/**
		 * Default destructor.
		 */
		~MainWindow();

	private:
		/**
		 * Setup screens to be displayed.
		 */
		void setupScreens();

	private:
		Ui::MainWindow* p_MainWindow = nullptr;
		Scipper::Instance m_Instance = {};
	};
}
