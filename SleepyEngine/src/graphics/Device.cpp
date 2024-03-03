#include "Graphics/Device.h"

#include "Utils/HResultException.h"

#include <dxgi1_4.h>
#include <d3d12.h>

void Device::Initialize(IDXGIAdapter1* pHardwareAdapter)
{
	// Create device
	HRESULT hardwareResult = D3D12CreateDevice(
		pHardwareAdapter,
		D3D_FEATURE_LEVEL_11_0, 
		__uuidof(ID3D12Device), 
		(void**)&m_pDevice
	);

	if (FAILED(hardwareResult))
	{
		IDXGIAdapter* pWarpAdapter;
		ThrowIfFailed(m_pDxgiFactory->EnumWarpAdapter(IID_PPV_
			ARGS(&pWarpAdapter)));
		// If the initialization fails, try to create WARP device
		ThrowIfFailed(D3D12CreateDevice(
			nullptr,
			D3D_FEATURE_LEVEL_11_0,
			__uuidof(ID3D12Device),
			(void**)&m_pDevice
		));
	}

	// Create device from WARP 

}

void Device::CleanUp()
{
	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}
