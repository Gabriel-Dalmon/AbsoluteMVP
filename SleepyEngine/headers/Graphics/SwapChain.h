#pragma once

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	void Initialize(IDXGIFactory4* pDgxiFactory, CommandQueue* pCommandQueue, Device* pDevice, Window* pWindow);
	void Release();

	// GETTERS & SETTERS
	inline IDXGISwapChain* GetD3DSwapChain()const { return m_pD3DSwapChain; };
	inline ID3D12Resource** GetSwapChainBuffer() { return m_swapChainBuffer; }
	inline ID3D12Resource* GetCurrentBackBuffer()const { return m_swapChainBuffer[m_currentBackBuffer]; };
	inline int GetCurrentBackBufferIndex()const { return m_currentBackBuffer; };
	inline void NextBackBuffer() { m_currentBackBuffer = (m_currentBackBuffer + 1) % SWAP_CHAIN_BUFFER_COUNT; }

private:
	void CreateSwapChain(IDXGIFactory4* pDgxiFactory, CommandQueue* pCommandQueue, Device* pDevice, Window* pWindow);
	void BindSwapChainBuffers(Device* pDevice);

private:
	IDXGISwapChain* m_pD3DSwapChain = nullptr;
	int m_currentBackBuffer = 0;
	ID3D12Resource* m_swapChainBuffer[SWAP_CHAIN_BUFFER_COUNT];
};