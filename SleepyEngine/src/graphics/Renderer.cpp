#include "pch.h"

Renderer::Renderer()
{
	m_requiredComponentsFlags = TRANSFORM | MESH_REFERENCE | SHADER_REFERENCE;
	m_pWindow = new Window();
	m_pDevice = new Device();
	m_pSwapChain = new SwapChain();
	m_pViewPort = new D3D12_VIEWPORT();
	m_pScissorRect = new tagRECT();
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
		EnableAdditionalD3D12Debug();
		m_pWindow->Initialize(hInstance, rendererDescriptor);
		ThrowIfFailed(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&m_pDxgiFactory));
		m_pDevice->Initialize();
		CreateFrameResources();
		CreateCommandObjects();
		m_pSwapChain->Initialize(m_pDxgiFactory, m_pCommandQueue, m_pDevice, m_pWindow);
		RecoverDescriptorSize();
		CreateDescriptorHeaps();
		CreateRenderTargetView();

		// Open the command list to instruct the GPU during initialization
		m_pCurrentFrameResource->ResetCommandAllocator();
		m_pCommandList->Reset(m_pCurrentFrameResource->GetD3DCommandAllocator(), nullptr);

		CreateDepthStencilView(rendererDescriptor);
		SetViewport(rendererDescriptor->windowWidth, rendererDescriptor->windowHeight);
		SetScissorRect(rendererDescriptor->windowWidth, rendererDescriptor->windowHeight);

		ThrowIfFailed(m_pCommandList->Close());
		ID3D12CommandList* cmdsLists[] = { m_pCommandList };
		m_pCommandQueue->Execute(_countof(cmdsLists), cmdsLists);
		m_pCommandQueue->Flush();
	}
	catch (HResultException& error) {
		OutputDebugString(error.ToString().c_str());
		MessageBox(nullptr, error.ToString().c_str(), L"HRESULT ERROR", MB_OK);
	}
}

void Renderer::EnableAdditionalD3D12Debug()
{
	ID3D12Debug* pDebugController;
	ThrowIfFailed(D3D12GetDebugInterface(__uuidof(ID3D12Debug), (void**)&pDebugController)); //should throw error
	pDebugController->EnableDebugLayer();
	std::cout << "Debug Layer Enabled" << std::endl;
}

void Renderer::CreateFrameResources()
{
	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i)
	{
		m_frameResources[i] = new FrameResource();
		m_frameResources[i]->Initialize(m_pDevice->GetD3DDevice());
	}
	m_pCurrentFrameResource = m_frameResources[m_currentFrameResourceIndex];
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

void Renderer::RecoverDescriptorSize()
{
	m_RTVDescriptorSize = m_pDevice->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_DSVDescriptorSize = m_pDevice->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	/*m_CBVSRVUAVDescriptorSize = m_pDevice->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV); */
}

void Renderer::CreateDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC RTVHeapDesc;
	RTVHeapDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	RTVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RTVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	RTVHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateDescriptorHeap(&RTVHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pRTVHeap));

	D3D12_DESCRIPTOR_HEAP_DESC DSVHeapDesc;
	DSVHeapDesc.NumDescriptors = 1;
	DSVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DSVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DSVHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateDescriptorHeap(&DSVHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pDSVHeap));
}

void Renderer::CreateRenderTargetView()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE RTVHeapHandle(GetCurrentBackBufferView());

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		m_pDevice->GetD3DDevice()->CreateRenderTargetView(m_pSwapChain->GetSwapChainBuffer()[i], nullptr, RTVHeapHandle);
		RTVHeapHandle.Offset(1, m_RTVDescriptorSize);
	}
}

void Renderer::CreateDepthStencilView(RendererDescriptor* rendererDescriptor)
{
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = rendererDescriptor->windowWidth;
	depthStencilDesc.Height = rendererDescriptor->windowHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = m_pDevice->Get4xMSAAState() ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_pDevice->Get4xMSAAState() ? (m_pDevice->Get4xMSAAQuality() - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// Describes a value used to optimize clear operations for a particular resource.
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_clear_value
	D3D12_CLEAR_VALUE optClear;
	optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
	ThrowIfFailed(m_pDevice->GetD3DDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		__uuidof(ID3D12Resource),
		(void**)&m_pDepthStencilBuffer
	));

	m_pDevice->GetD3DDevice()->CreateDepthStencilView(m_pDepthStencilBuffer, nullptr, GetDepthStencilView()); //nullptr for default mip level 0

	CD3DX12_RESOURCE_BARRIER ressourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_pDepthStencilBuffer,
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE);
	m_pCommandList->ResourceBarrier(
		1,
		&ressourceBarrier
	);
}

// Should pass a viewport descriptor rather than clientWidth and clientHeight
void Renderer::SetViewport(UINT clientWidth, UINT clientHeight)
{
	m_pViewPort->TopLeftX = 0.0f;
	m_pViewPort->TopLeftY = 0.0f;
	m_pViewPort->Width = static_cast<float>(clientWidth);
	m_pViewPort->Height = static_cast<float>(clientHeight);
	m_pViewPort->MinDepth = 0.0f;
	m_pViewPort->MaxDepth = 1.0f;
}

void Renderer::SetScissorRect(UINT clientWidth, UINT clientHeight)
{
	m_pScissorRect->left = 0;
	m_pScissorRect->top = 0;
	m_pScissorRect->right = clientWidth;
	m_pScissorRect->bottom = clientHeight;
}

void Renderer::Update(float deltaTime)
{
	WaitForFrameResource();
	UpdateBuffers();
	RenderFrame();
}

void Renderer::WaitForFrameResource()
{
	// Cycle through the circular frame resource array.
	m_currentFrameResourceIndex = (m_currentFrameResourceIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
	m_pCurrentFrameResource = m_frameResources[m_currentFrameResourceIndex];
	// Has the GPU finished processing the commands of the current frame 
	// resource. If not, wait until the GPU has completed commands up to
	// this fence point.
	if (m_pCurrentFrameResource->GetFence() != 0 &&
		m_pCommandQueue->GetLastCompletedFence() < m_pCurrentFrameResource->GetFence())
	{
		std::cout << "Waiting for frame resource to be ready. LastFence : " << m_pCommandQueue->GetLastCompletedFence() << "Fence : " << m_pCurrentFrameResource->GetFence() << m_currentFrameResourceIndex << std::endl;
		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
		ThrowIfFailed(m_pCommandQueue->SetEventOnFenceCompletion(m_pCurrentFrameResource->GetFence(), eventHandle));
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
	else
	{
		std::cout << "Frame resource is ready" << m_pCommandQueue->GetLastCompletedFence() << "Fence : " << m_pCurrentFrameResource->GetFence() << " Frame Resource : " << m_currentFrameResourceIndex << std::endl;
	}
}

void Renderer::UpdateBuffers()
{

}

void Renderer::RenderFrame()
{
	ResetRendering();

	D3D12_CPU_DESCRIPTOR_HANDLE currentBackBufferView = GetCurrentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE dephtStencilView = GetDepthStencilView();

	XMVECTORF32 color = Colors::LightSteelBlue;
	switch (m_currentFrameResourceIndex)
	{
		case 1:
			color = Colors::Gold;
			break;
		case 2:
			color = Colors::OliveDrab;
			break;
	}
	

	m_pCommandList->RSSetViewports(1, m_pViewPort);
	m_pCommandList->RSSetScissorRects(1, m_pScissorRect);	

	m_pCommandList->ClearRenderTargetView(currentBackBufferView, color, 0, nullptr);
	m_pCommandList->ClearDepthStencilView(dephtStencilView, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	m_pCommandList->OMSetRenderTargets(1, &currentBackBufferView, true, &dephtStencilView);

	m_pCommandList->SetGraphicsRootSignature(m_pRootSignature);

	CloseAndExecuteRendering();
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

void Renderer::ResetRendering()
{
	HRESULT hr = m_pCurrentFrameResource->ResetCommandAllocator();
	ID3D12CommandAllocator* cmdAlloc = m_pCurrentFrameResource->GetD3DCommandAllocator();
	hr = m_pCommandList->Reset(cmdAlloc, nullptr); //nullptr should be replaced with a pso
	std::cout << hr << std::endl;

	ID3D12Resource* currBackBuff = m_pSwapChain->GetCurrentBackBuffer();
	CD3DX12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		currBackBuff,
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	m_pCommandList->ResourceBarrier(1, &resourceBarrier);
}

void Renderer::CloseAndExecuteRendering()
{
	CD3DX12_RESOURCE_BARRIER resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(m_pSwapChain->GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_pCommandList->ResourceBarrier(1, &resourceBarrier);

	m_pCommandList->Close();

	ID3D12CommandList* cmdsLists[] = { m_pCommandList };
	m_pCommandQueue->Execute(_countof(cmdsLists), cmdsLists);

	ThrowIfFailed(m_pSwapChain->GetD3DSwapChain()->Present(0, 0));

	std::cout << "Frame " << m_currentFrameResourceIndex << " presented" << std::endl;
	m_pSwapChain->NextBackBuffer();
	m_pCurrentFrameResource->IncrementFence();
	if (m_currentFrameResourceIndex == 0)
	{
		m_pCommandQueue->Signal(m_pCurrentFrameResource->GetFence());
	}
	std::cout << "Next fence value : " << m_pCurrentFrameResource->GetFence() << " Currently on " << m_pCommandQueue->GetLastCompletedFence() << std::endl;
}