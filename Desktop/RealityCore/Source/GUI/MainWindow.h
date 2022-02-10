#pragma once

#include <QMainWindow>

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
		Ui::MainWindow* p_MainWindow = nullptr;
	};
}
