#pragma once

struct RendererEntityData : public SystemEntityData
{
	Transform* transform;
	MeshReference* meshReference;
	ShaderReference* shaderReference;
};

struct RendererDescriptor
{
	int windowWidth = 400;
	int windowHeight = 400;
	LPCWSTR hAppTitle = L"SleepyEngine";
	HICON hAppIcon = nullptr;
	HICON hAppIconSmall = nullptr;
	HCURSOR hAppCursor = nullptr;
	LPCWSTR hAppClassName = L"SleepyEngine";
};

class Renderer : public System
{
public:
	Renderer();
	~Renderer();

	void Initialize(HINSTANCE hInstance, RendererDescriptor* rendererDescriptor);
	void Release();

	void UpdateBuffers();
	void RenderFrame();

	void UNSAFE_AddEntity(Entity* entity) override;
	void UNSAFE_RemoveEntity(Entity* entity) override;

private:
	void CreateFrameResources();
	void CreateCommandObjects();
	void CreateDescriptorHeaps();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void SetViewport();
	void SetScissorRect();


private:
	Window* m_pWindow = nullptr;

	IDXGIFactory4* m_pDxgiFactory = nullptr;
	Device* m_pDevice = nullptr;

	FrameResource* m_frameResources[SWAP_CHAIN_BUFFER_COUNT];
	FrameResource* m_pCurrentFrameResource = nullptr;
	int m_currentFrameResourceIndex = 0;

	SwapChain* m_pSwapChain = nullptr;
	ID3D12RootSignature* m_pRootSignature = nullptr;

	CommandQueue* m_pCommandQueue = nullptr;
	ID3D12GraphicsCommandList* m_pCommandList = nullptr;
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;

	ID3D12DescriptorHeap* m_pRtvHeap = nullptr;
	ID3D12DescriptorHeap* m_pDsvHeap = nullptr;

	std::vector<RendererEntityData*> m_entitiesDataList;
};