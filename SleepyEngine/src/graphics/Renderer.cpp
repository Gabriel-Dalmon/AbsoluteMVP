#include "pch.h"
#include "Graphics/Renderer.h"
#include "Graphics/Window.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"

#include "Utils/HResultException.h"

#include "d3dx12.h"

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
		BuildRootSignature();
	}
	catch (HResultException& e) {
		OutputDebugString(e.ToString().c_str());
	}
}

void Renderer::BuildRootSignature()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];
	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);
	//slotRootParameter[0].InitAsConstantBufferView(0);    

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	ID3DBlob* pSerializedRootSig;
	HRESULT hr = D3D12SerializeRootSignature(
		&rootSigDesc, 
		D3D_ROOT_SIGNATURE_VERSION_1, 
		&pSerializedRootSig, 
		NULL
	);

	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateRootSignature(
		0,
		pSerializedRootSig->GetBufferPointer(),
		pSerializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature))
	);
}

void Renderer::RenderFrame()
{
}

void Renderer::CleanUp()
{
	m_pSwapChain->CleanUp();
	m_pDevice->CleanUp();
	m_pWindow->CleanUp();
	m_pDxgiFactory->Release();
}

