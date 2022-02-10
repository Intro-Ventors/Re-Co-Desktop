#pragma once

namespace Scipper
{
	/**
	 * Reality Core screen capture abstract class.
	 * This class is the base class for all the classes in the screen capture API.
	 */
	class RScreenCapture
	{
	public:
		/**
		 * Default constructor.
		 */
		RScreenCapture() = default;

		/**
		 * Default virtual destructor.
		 */
		virtual ~RScreenCapture() = 0;
	};
}