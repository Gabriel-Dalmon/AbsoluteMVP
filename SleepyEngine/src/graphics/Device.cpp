#include "pch.h"

Device::Device()
{
}

Device::~Device()
{
}

void Device::Initialize(IDXGIFactory4* pDgxiFactory, unsigned int hardwareAdapterIndex)
{
	// Recover the hardware adapter
	IDXGIAdapter* pAdapter = nullptr;
	if (pDgxiFactory != nullptr)
	{
		ThrowIfFailed(pDgxiFactory->EnumAdapters(hardwareAdapterIndex, &pAdapter));
	}

	// Create device
	HRESULT hardwareResult = D3D12CreateDevice(
		pAdapter,
		D3D_FEATURE_LEVEL_11_0, 
		__uuidof(ID3D12Device), 
		(void**)&m_pD3DDevice
	);
	RELEASE(pAdapter);

	// Create a device from a WARP adapter if device creation failed with harware adapter
	if (FAILED(hardwareResult)) 
	{
		#if defined(DEBUG) || defined(_DEBUG)		
		OutputDebugStringA("Failed to create device with hardware adapter. Creating device with WARP adapter.\n");
		#endif // DEBUG

		ThrowIfFailed(pDgxiFactory->EnumWarpAdapter(__uuidof(IDXGIAdapter),(void**)&pAdapter));
		ThrowIfFailed(D3D12CreateDevice(
			nullptr,
			D3D_FEATURE_LEVEL_11_0,
			__uuidof(ID3D12Device),
			(void**)&m_pD3DDevice
		));
		pAdapter->Release();
	}
	Check4xMSAAQualitySupport();
}

void Device::Initialize(IDXGIAdapter* pAdapter)
{
	ThrowIfFailed(D3D12CreateDevice(
		pAdapter,
		D3D_FEATURE_LEVEL_11_0,
		__uuidof(ID3D12Device),
		(void**)&m_pD3DDevice
	));
	Check4xMSAAQualitySupport();
}

void Device::Check4xMSAAQualitySupport()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = BACK_BUFFER_FORMAT;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(m_pD3DDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels)));
	m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
}

void Device::Release()
{
	if (m_pD3DDevice)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
}
