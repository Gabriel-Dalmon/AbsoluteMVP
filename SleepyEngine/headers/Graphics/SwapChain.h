#pragma once

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	void Initialize(IDXGIFactory4* pDgxiFacotry, Device* pDevice, Window* pWindow);
	void CreateSwapChain(IDXGIFactory4* pDgxiFacotry, Device* pDevice, Window* pWindow);
	void Release();

private:
	IDXGISwapChain* m_pSwapChain = nullptr;
};