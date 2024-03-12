#include "pch.h"

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::Initialize(IDXGIFactory4* pDgxiFacotry, Device* pDevice, Window* pWindow)
{
    CreateSwapChain(pDgxiFacotry, pDevice, pWindow);
}

void SwapChain::CreateSwapChain(IDXGIFactory4* pDgxiFacotry, Device* pDevice, Window* pWindow)
{
    if (m_pSwapChain)
    {
        m_pSwapChain->Release();
        m_pSwapChain = nullptr;
    }
    DXGI_SWAP_CHAIN_DESC swapChainDescriptor;
    swapChainDescriptor.BufferDesc.Width = pWindow->GetWindowWidth();
    swapChainDescriptor.BufferDesc.Height = pWindow->GetWindowHeight();
    swapChainDescriptor.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescriptor.BufferDesc.Format = BACK_BUFFER_FORMAT;
    swapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDescriptor.SampleDesc.Count = pDevice->Get4xMSAAState() ? 4 : 1;
    swapChainDescriptor.SampleDesc.Quality = pDevice->Get4xMSAAState() ? (pDevice->Get4xMSAAQuality() - 1) : 0;
    swapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescriptor.BufferCount = SWAP_CHAIN_BUFFER_COUNT;
    swapChainDescriptor.OutputWindow = pWindow->GetWindowHandle();
    swapChainDescriptor.Windowed = true;
    swapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    ThrowIfFailed(pDgxiFacotry->CreateSwapChain(pDevice->GetD3DDevice(), &swapChainDescriptor, &m_pSwapChain))
}


void SwapChain::Release()
{
    if (m_pSwapChain)
    {
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
}
