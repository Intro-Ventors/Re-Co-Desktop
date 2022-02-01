#pragma once

#include "RScreenCapture.hpp"

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
		 * Default constructor.
		 */
		Screen() = default;
	};
}