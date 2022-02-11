#pragma once

#include "RScreenCapture.hpp"
#include <QString>

namespace Scipper
{
	/**
	 * Screen class.
	 * This class represents a single screen in the case of a multiple display format.
	 */
	class Screen final : public RScreenCapture
	{
	public:
		/**
		 * Constructor.
		 * 
		 * @param name The name of the screen.
		 */
		Screen(QString name);

	private:
		QString m_Name;
	};
}