#include "pch.h"

Renderer::Renderer()
{
	m_requiredComponentsFlags = TRANSFORM | MESH_REFERENCE | SHADER_REFERENCE;
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

void Renderer::Initialize(HINSTANCE hInstance, RendererDescriptor* rendererDescriptor)
{
	try {
		m_pWindow->Initialize(hInstance, rendererDescriptor->windowWidth, rendererDescriptor->windowHeight);
		ThrowIfFailed(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&m_pDxgiFactory));
		m_pDevice->Initialize();
		m_pSwapChain->Initialize(m_pDxgiFactory, m_pDevice, m_pWindow);
	}
	catch (HResultException& e) {
		OutputDebugString(e.ToString().c_str());
	}
}

void Renderer::CreateCommandObjects()
{
	// Create the command queue.
	m_pCommandQueue = new CommandQueue();
	m_pCommandQueue->Initialize(m_pDevice);

	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_pCommandAllocator));
	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pCommandAllocator, nullptr, __uuidof(ID3D12CommandList), (void**)&m_pCommandList));
	ThrowIfFailed(m_pCommandList->Close());
}

void Renderer::CreateDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateDescriptorHeap(&rtvHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pRtvHeap));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateDescriptorHeap(&dsvHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pDsvHeap));
}

void Renderer::CreateRenderTargetView()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_pRtvHeap->GetCPUDescriptorHandleForHeapStart());

	// Should create render target view from FrameResource
	/*for (UINT i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		ThrowIfFailed(m_pSwapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)&m_pSwapChainBuffer[i]));
		m_pDevice->GetD3DDevice()->CreateRenderTargetView(m_pSwapChainBuffer[i], nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, m_rtvDescriptorSize);
	}*/
}

void Renderer::RenderFrame()
{
}

void Renderer::Release()
{
	m_pSwapChain->Release();
	m_pDevice->Release();
	m_pWindow->Release();
	m_pDxgiFactory->Release();
}

void Renderer::UNSAFE_AddEntity(Entity* entity)
{
	RendererEntityData* entityData = new RendererEntityData();
	entityData->entity = entity;
	entityData->transform = entity->GetComponent<Transform>();
	entityData->meshReference = entity->GetComponent<MeshReference>();
	entityData->shaderReference = entity->GetComponent<ShaderReference>();
	m_entitiesDataList.push_back(entityData);
}

void Renderer::UNSAFE_RemoveEntity(Entity* entity)
{
	for (int i = 0; i < m_entitiesDataList.size(); i++)
	{
		if (m_entitiesDataList[i]->entity == entity)
		{
			delete m_entitiesDataList[i];
			m_entitiesDataList.erase(m_entitiesDataList.begin() + i);
		}
	}
}

