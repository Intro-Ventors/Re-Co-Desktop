#pragma once

#include <QWidget>
#include <QLabel>
#include <mutex>
#include <atomic>

#include "../Scipper/FrameCapture.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

namespace GUI
{
	/**
	 * Window widget object.
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
		 * Set a frame capture object pointer to the widget.
		 *
		 * @param pFrameCapture The frame capture object pointer.
		 */
		void setFrameCapture(std::shared_ptr<Scipper::FrameCapture> pFrameCapture);

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
		std::atomic<std::chrono::nanoseconds> m_Delta;
		std::shared_ptr<Scipper::FrameCapture> m_pFrameCapture = nullptr;
		std::shared_ptr<Scipper::ImageData> m_pImage = nullptr;
		Ui::Window* m_pScreen = nullptr;
	};
}