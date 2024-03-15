#pragma once

struct RendererEntityData : public SystemEntityData
{
	Transform* pTransform;
	MeshReference* pMeshReference;
	ShaderReference* pShaderReference;
};

struct RendererDescriptor
{
	UINT windowWidth = 400;
	UINT windowHeight = 400;
	LPCWSTR hAppTitle = L"SleepyEngine";
	HICON hAppIcon = nullptr;
	HICON hAppIconSmall = nullptr;
	HCURSOR hAppCursor = nullptr;
	LPCWSTR hAppClassName = L"SleepyEngine";
};

/*struct RenderItem
{
	RenderItem() = default;
	XMFLOAT4X4 World = MathHelper::Identity4x4();

	int NumFramesDirty = gNumFrameResources;

	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT ObjCBIndex = -1;

	MeshGeometry* Geo = nullptr;

	// Primitive topology.
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// DrawIndexedInstanced parameters.
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	int BaseVertexLocation = 0;
};*/

class Renderer : public System
{
public:
	Renderer();
	~Renderer();

	void Initialize(HINSTANCE hInstance, RendererDescriptor* rendererDescriptor);
	void Release();

	void Update(float deltaTime) override;
	void WaitForFrameResource();

	void UpdateBuffers();
	void RenderFrame();
	void RenderFrameEmpty();

	void UNSAFE_AddEntity(Entity* entity) override;
	void UNSAFE_RemoveEntity(Entity* entity) override;

public:
	// GETTERS / SETTERS
	inline Device* GetDevice() { return m_pDevice; };
	inline CommandQueue* GetCommandQueue() { return m_pCommandQueue; };
	inline ShaderColor* GetColorShader() { return m_pColorShader; };

private:
	void ResetRendering();
	void ExecuteRendering();

private:
	void EnableAdditionalD3D12Debug();
	void RecoverDescriptorSize();
	void CreateFrameResources();

	void CreateCommandObjects();
	void CreateRTVAndDSVDescriptorHeaps();
	void CreateRenderTargetView();
	void CreateDepthStencilView(RendererDescriptor* rendererDescriptor);
	void SetViewport(UINT clientWidth, UINT clientHeight);
	void SetScissorRect(UINT clientWidth, UINT clientHeight);

	// Temporary 
	void CreateShaders(); // Shaders creation should be moved to the ResourceAllocator
	void CreateDescriptorHeaps();
	void BuildConstantBufferViews();

private:
	inline D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView()const { return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_pRTVHeap->GetCPUDescriptorHandleForHeapStart(), m_pSwapChain->GetCurrentBackBufferIndex(), m_RTVDescriptorSize); };
	inline D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView()const { return m_pDSVHeap->GetCPUDescriptorHandleForHeapStart(); }

private:
	Window* m_pWindow = nullptr;

	IDXGIFactory4* m_pDxgiFactory = nullptr;
	Device* m_pDevice = nullptr;

	FrameResource* m_frameResources[SWAP_CHAIN_BUFFER_COUNT];
	FrameResource* m_pCurrentFrameResource = nullptr;
	int m_currentFrameResourceIndex = 0;

	SwapChain* m_pSwapChain = nullptr;

	CommandQueue* m_pCommandQueue = nullptr;
	ID3D12GraphicsCommandList* m_pCommandList = nullptr;
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;

	ID3D12DescriptorHeap* m_pCBVHeap = nullptr;

	ID3D12DescriptorHeap* m_pRTVHeap = nullptr;
	UINT m_RTVDescriptorSize = 0;
	ID3D12DescriptorHeap* m_pDSVHeap = nullptr;
	UINT m_DSVDescriptorSize = 0;
	ID3D12Resource* m_pDepthStencilBuffer = nullptr;

	UINT m_CBVSRVUAVDescriptorSize = 0;

	D3D12_VIEWPORT* m_pViewPort = nullptr;
	tagRECT* m_pScissorRect = nullptr;

	XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	TmpCamera* m_pCamera = nullptr;

	ShaderColor* m_pColorShader = nullptr;
	std::vector<RendererEntityData*> m_entitiesDataList;
};
