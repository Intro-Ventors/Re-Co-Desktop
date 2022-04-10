// Copyright (c) 2022 Intro-Ventors

#pragma once

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>

#include "ScreenWidget.hpp"
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
		 * @param instance The scipper instance.
		 * @param pParent The parent object. Default is nullptr.
		 */
		MainWindow(Scipper::Instance& instance, QWidget* pParent = nullptr);

		/**
		 * Default destructor.
		 */
		~MainWindow();

		/**
		 * Override the close event.
		 *
		 * @param pCloseEvent The close event pointer.
		 */
		void closeEvent(QCloseEvent* pCloseEvent) override;

		/**
		 * Set the window to close-able mode.
		 */
		void toggleCloseable() { m_bCloseable = true; }

		/**
		 * Refresh the screens to be displayed.
		 */
		void refreshScreens();

	private:
		/**
		 * Create the about menu.
		 */
		void setupAboutMenu();

		/**
		 * Create the login menu.
		 */
		void setupLoginMenu();

		/**
		 * Setup windows to be displayed.
		 */
		void setupWindows();

	private:
		std::vector<std::shared_ptr<ScreenWidget>> m_ScreenWidgets;

		Ui::MainWindow* m_pMainWindow = nullptr;
		QScrollArea* m_pScrollArea = nullptr;
		QVBoxLayout* m_pBoxLayout = nullptr;
		Scipper::Instance& m_Instance;

		bool m_bCloseable = false;
	};
}
