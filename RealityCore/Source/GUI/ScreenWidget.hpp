#pragma once

#include <QWidget>
#include <QLabel>
#include <mutex>

#include "../Scipper/Screen.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Screen; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * Screen widget object.
	 * This object is used to render a single image to the user.
	 */
	class ScreenWidget : public QWidget
	{
		Q_OBJECT

	public:
		/**
		 * Constructor.
		 *
		 * @param pParent The parent widget pointer.
		 */
		ScreenWidget(QWidget* pParent = nullptr);

		/**
		 * Default destructor.
		 */
		~ScreenWidget();

		/**
		 * Override the paint event function.
		 * 
		 * @param pEvent The event pointer.
		 */
		void paintEvent(QPaintEvent* pEvent) override;

		/**
		 * Set a screen object pointer to the widget.
		 * 
		 * @param pScreen The screen object pointer.
		 */
		void setScreen(std::shared_ptr<Scipper::Screen> pScreen);

		/**
		 * Get the label pointer of the screen widget.
		 * 
		 * @return The label pointer.
		 */
		QLabel* getLabel() const;

	private slots:
		/**
		 * Slot to handle the new image signal.
		 *
		 * @param image The new image.
		 */
		void onNewFrame(std::shared_ptr<Scipper::ImageData> image);

	private:
		std::shared_ptr<Scipper::Screen> m_pScipperScreen = nullptr;
		std::shared_ptr<Scipper::ImageData> m_pImage = nullptr;
		Ui::Screen* m_pScreen = nullptr;
	};
}