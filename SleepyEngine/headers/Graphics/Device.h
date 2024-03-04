#pragma once

class ID3D12Device;
class IDXGIFactory4;
class IDXGIAdapter;

class Device
{
public:
	Device();
	~Device();

	void Initialize(IDXGIFactory4* pDgxiFactory = nullptr, unsigned int hardwareAdapterIndex = 0);
	void Initialize(IDXGIAdapter* pAdapter);
	void Check4xMSAAQualitySupport();
	void CleanUp();

	inline ID3D12Device* GetD3DDevice() const { return m_pD3DDevice; }
	inline UINT Get4xMSAAQuality() const { return m_4xMsaaQuality; }
	inline bool Get4xMSAAState() const { return m_4xMsaaState; }

private:
		ID3D12Device* m_pD3DDevice = nullptr;

		UINT m_4xMsaaQuality = 0;
		bool m_4xMsaaState = false;
};