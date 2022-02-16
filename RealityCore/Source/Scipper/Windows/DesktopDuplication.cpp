#include "DesktopDuplication.hpp"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <stdint.h>

#include <string>
#include <functional>
#include <stdexcept>

#include <SDKDDKVer.h>

namespace Scipper
{
	DesktopDuplication::DesktopDuplication()
	{
		HDESK hDesk = OpenInputDesktop(0, FALSE, GENERIC_ALL);
		if (!hDesk)
			throw std::runtime_error("Failed to open the input desktop.");

		const bool deskAttached = SetThreadDesktop(hDesk);
		CloseDesktop(hDesk);

		hDesk = nullptr;
		if (!deskAttached)
			throw std::runtime_error("Failed to attach the recording thread to the desktop.");

		// Initialize the DirectX framework.
		HRESULT result = S_OK;

		D3D_DRIVER_TYPE driverTypes[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
		};

		const auto driverTypeCount = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_1
		};

		const auto featureLevelCount = ARRAYSIZE(featureLevels);

		D3D_FEATURE_LEVEL featureLevel;

		for (size_t i = 0; i < driverTypeCount; i++)
		{
			result = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, 0, featureLevels, static_cast<UINT>(featureLevelCount), D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pDeviceContext);

			if (SUCCEEDED(result))
				break;
		}

		if (FAILED(result))
			throw std::runtime_error("Failed to create the DirectX 11 device with the required features and driver types.");
	}

	DesktopDuplication::~DesktopDuplication()
	{
	}
}