#pragma once

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>

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
		 * Setup windows to be displayed.
		 */
		void setupWindows();

	private:
		Ui::MainWindow* m_pMainWindow = nullptr;
		QScrollArea* m_pScrollArea = nullptr;
		QVBoxLayout* m_pVBoxLayout = nullptr;
		Scipper::Instance m_Instance = {};
	};
}
