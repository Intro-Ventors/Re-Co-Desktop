#include "GUI/ApplicationGUI.hpp"

#ifdef RECO_SHARED
#define RECO_API	__declspec(dllexport)

#else
#define RECO_API	

#endif // RECO_SHARED


extern "C"
{
	struct RECO_API RealityCoreInstance
	{
		/**
		 * Constructor.
		 *
		 * @param argc The argument count.
		 * @param argv The variadic arguments.
		 */
		RealityCoreInstance(int argc = 0, char* argv[] = nullptr) :
			m_Application(argc, argv, m_Instance) {}

		Scipper::Instance m_Instance;
		GUI::ApplicationGUI m_Application;
	};

	/**
	 * Create a new instance object.
	 *
	 * @return The instance object pointer.
	 */
	RECO_API RealityCoreInstance* CreateInstance()
	{
		return new RealityCoreInstance();
	}

	/**
	 * Run the instance object.
	 *
	 * @param pInstance The instance pointer.
	 */
	RECO_API int RunInstance(RealityCoreInstance* pInstance)
	{
		return pInstance->m_Application.run();
	}

	/**
	 * Destroy the instance.
	 *
	 * @param pInstance The instance pointer to delete.
	 */
	RECO_API void DestroyInstance(RealityCoreInstance* pInstance)
	{
		delete pInstance;
	}
}

#ifndef RECO_SHARED

int main(int argc, char* argv[])
{
	// Create the instance.
	auto pInstance = CreateInstance();

	// Run the instance.
	const auto result = RunInstance(pInstance);

	// Destroy the instance when exiting.
	DestroyInstance(pInstance);

	return result;
}

#endif // !RECO_SHARED