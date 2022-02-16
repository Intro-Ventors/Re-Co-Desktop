#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include <vector>

#include <d3d11.h>
#include <dxgi1_2.h>

namespace Scipper
{
	struct Bitmap
	{
		std::vector<uint8_t> m_Buffer = {};
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};

	class DesktopDuplication final
	{
	public:
		DesktopDuplication();
		~DesktopDuplication();

		Bitmap capture();

	private:
		DXGI_OUTPUT_DESC m_OutputDesc;
		Bitmap m_Bitmap = {};

		ID3D11Device* m_pDevice = nullptr;
		ID3D11DeviceContext* m_pDeviceContext = nullptr;
		IDXGIOutputDuplication* m_pDesktopDuplication = nullptr;

		int32_t m_FrameNumber = 0;
		bool m_bHaveFrameLock = false;
	};
}