#pragma once

class ID3D12Device;
class IDXGIAdapter1;

class Device
{
public:
	Device();
	~Device();

	void Initialize(IDXGIAdapter1* pHardwareAdapter = nullptr);
	void CleanUp();

private:
		ID3D12Device* m_pDevice = nullptr;
};