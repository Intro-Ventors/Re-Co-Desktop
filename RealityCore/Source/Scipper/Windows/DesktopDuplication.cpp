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

#pragma comment(lib,"d3d11.lib")

namespace Scipper
{
	DesktopDuplication::DesktopDuplication()
	{
		// Open the input desktop.
		HDESK hDesk = OpenInputDesktop(0, FALSE, GENERIC_ALL);
		if (!hDesk)
			throw std::runtime_error("Failed to open the input desktop.");

		//const bool deskAttached = SetThreadDesktop(hDesk) != 0;
		CloseDesktop(hDesk);

		//hDesk = nullptr;
		//if (!deskAttached)
		//	throw std::runtime_error("Failed to attach the recording thread to the desktop.");

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

		// Get DXGI device
		IDXGIDevice* dxgiDevice = nullptr;
		result = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (FAILED(result))
			throw std::runtime_error("D3DDevice->QueryInterface failed!");

		// Get DXGI adapter
		IDXGIAdapter* dxgiAdapter = nullptr;
		result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));
		dxgiDevice->Release();
		dxgiDevice = nullptr;
		if (FAILED(result))
		{
			throw std::runtime_error("dxgiDevice->GetParent failed!");
			//return ProcessFailure(m_Device, L"Failed to get parent DXGI Adapter", L"Error", hr, SystemTransitionsExpectedErrors);
		}

		// Get output
		IDXGIOutput* dxgiOutput = nullptr;
		result = dxgiAdapter->EnumOutputs(m_FrameNumber, &dxgiOutput);
		dxgiAdapter->Release();
		dxgiAdapter = nullptr;
		if (FAILED(result))
		{
			throw std::runtime_error("dxgiAdapter->EnumOutputs failed!");
			//return ProcessFailure(m_Device, L"Failed to get specified output in DUPLICATIONMANAGER", L"Error", hr, EnumOutputsExpectedErrors);
		}

		dxgiOutput->GetDesc(&m_OutputDesc);

		// QI for Output 1
		IDXGIOutput1* dxgiOutput1 = nullptr;
		result = dxgiOutput->QueryInterface(__uuidof(dxgiOutput1), reinterpret_cast<void**>(&dxgiOutput1));
		dxgiOutput->Release();
		dxgiOutput = nullptr;
		if (FAILED(result))
			throw std::runtime_error("dxgiOutput->QueryInterface failed!");

		// Create desktop duplication
		result = dxgiOutput1->DuplicateOutput(m_pDevice, &m_pDesktopDuplication);
		dxgiOutput1->Release();
		dxgiOutput1 = nullptr;
		if (FAILED(result))
		{
			if (result == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE)
			{
				//MessageBoxW(nullptr, L"There is already the maximum number of applications using the Desktop Duplication API running, please close one of those applications and then try again.", L"Error", MB_OK);
				throw std::runtime_error("Too many desktop recorders already active");
			}
			throw std::runtime_error("DuplicateOutput failed!");
			//return ProcessFailure(m_Device, L"Failed to get duplicate output in DUPLICATIONMANAGER", L"Error", hr, CreateDuplicationExpectedErrors);
		}

	}

	DesktopDuplication::~DesktopDuplication()
	{
		if (m_pDesktopDuplication)
			m_pDesktopDuplication->Release();

		if (m_pDeviceContext)
			m_pDeviceContext->Release();

		if (m_pDevice)
			m_pDevice->Release();
	}

	Bitmap DesktopDuplication::capture()
	{
		if (!m_pDesktopDuplication)
			return m_Bitmap;

		HRESULT result = S_OK;

		// according to the docs, it's best for performance if we hang onto the frame for as long as possible,
		// and only release the previous frame immediately before acquiring the next one. Something about
		// the OS coalescing updates, so that it doesn't have to store them as distinct things.
		if (m_bHaveFrameLock)
		{
			m_bHaveFrameLock = false;
			result = m_pDesktopDuplication->ReleaseFrame();
			// ignore response
		}

		IDXGIResource* deskRes = nullptr;
		DXGI_OUTDUPL_FRAME_INFO frameInfo;
		result = m_pDesktopDuplication->AcquireNextFrame(0, &frameInfo, &deskRes);
		if (result == DXGI_ERROR_WAIT_TIMEOUT)
		{
			// nothing to see here
			return m_Bitmap;
		}
		if (FAILED(result))
		{
			// perhaps shutdown and reinitialize
			OutputDebugStringA("Acquire failed");
			return m_Bitmap;
		}

		m_bHaveFrameLock = true;

		ID3D11Texture2D* gpuTex = nullptr;
		result = deskRes->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&gpuTex));
		deskRes->Release();
		deskRes = nullptr;
		if (FAILED(result))
		{
			// not expected
			return m_Bitmap;
		}

		bool ok = true;

		D3D11_TEXTURE2D_DESC desc;
		gpuTex->GetDesc(&desc);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.MiscFlags = 0; // D3D11_RESOURCE_MISC_GDI_COMPATIBLE ?
		ID3D11Texture2D* cpuTex = nullptr;
		result = m_pDevice->CreateTexture2D(&desc, nullptr, &cpuTex);
		if (SUCCEEDED(result))
		{
			m_pDeviceContext->CopyResource(cpuTex, gpuTex);
		}
		else
		{
			// not expected
			ok = false;
		}

		//UINT                     subresource = D3D11CalcSubresource(0, 0, 0);
		D3D11_MAPPED_SUBRESOURCE sr;
		result = m_pDeviceContext->Map(cpuTex, 0, D3D11_MAP_READ, 0, &sr);
		if (SUCCEEDED(result))
		{
			if (m_Bitmap.m_Width != desc.Width || m_Bitmap.m_Height != desc.Height)
			{
				m_Bitmap.m_Width = desc.Width;
				m_Bitmap.m_Height = desc.Height;
				m_Bitmap.m_Buffer.resize(desc.Width * desc.Height);
			}
			for (int y = 0; y < static_cast<int>(desc.Height); y++)
				memcpy(m_Bitmap.m_Buffer.data() + y * desc.Width, reinterpret_cast<uint8_t*>(sr.pData) + sr.RowPitch * y, desc.Width * 4);
			m_pDeviceContext->Unmap(cpuTex, 0);
		}
		else
		{
			ok = false;
		}

		cpuTex->Release();
		gpuTex->Release();

		return m_Bitmap;
	}
}