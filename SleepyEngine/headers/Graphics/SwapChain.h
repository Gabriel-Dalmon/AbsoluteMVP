#pragma once

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	void Initialize(IDXGIFactory4* pDgxiFacotry, Device* pDevice, Window* pWindow);
	void Release();

	// GETTERS & SETTERS
	inline IDXGISwapChain* GetD3DSwapChain() { return m_pD3DSwapChain; };
	inline ID3D12Resource** GetSwapChainBuffer() { return m_swapChainBuffer; }

private:
	void CreateSwapChain(IDXGIFactory4* pDgxiFacotry, Device* pDevice, Window* pWindow);
	void BindSwapChainBuffers(Device* pDevice);

private:
	IDXGISwapChain* m_pD3DSwapChain = nullptr;
	int m_currentBackBuffer = 0;
	ID3D12Resource* m_swapChainBuffer[SWAP_CHAIN_BUFFER_COUNT];
};