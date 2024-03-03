#include "Graphics/Renderer.h"
#include "Graphics/Window.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"

#include "Utils/HResultException.h"

#include <dxgi1_4.h>

Renderer::Renderer()
{
	m_pWindow = new Window();
	m_pDevice = new Device();
	m_pSwapChain = new SwapChain();
}

Renderer::~Renderer()
{
	delete m_pSwapChain;
	delete m_pDevice;
	delete m_pWindow;
}

void Renderer::Initialize(HINSTANCE hInstance, int windowWidth, int windowHeight)
{
	try {
		m_pWindow->Initialize(hInstance, windowWidth, windowHeight);
		ThrowIfFailed(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&m_pDxgiFactory));
		m_pDevice->Initialize();
		m_pSwapChain->Initialize(m_pDxgiFactory, m_pDevice, m_pWindow);
	}
	catch (HResultException& e) {
		OutputDebugString(e.ToString().c_str());
	}
}

void Renderer::CleanUp()
{
	m_pSwapChain->CleanUp();
	m_pDevice->CleanUp();
	m_pWindow->CleanUp();
	m_pDxgiFactory->Release();
}

