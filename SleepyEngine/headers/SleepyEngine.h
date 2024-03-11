#pragma once

struct ObjectConstants
{
    XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

struct Texture
{
    // Unique material name for lookup.
    std::string Name;

    std::wstring Filename;

    Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;
};

// Simple struct to represent a material for our demos.  A production 3D engine
// would likely create a class hierarchy of Materials.
struct Material
{
    // Unique material name for lookup.
    std::string Name;

    // Index into constant buffer corresponding to this material.
    int MatCBIndex = -1;

    // Index into SRV heap for diffuse texture.
    int DiffuseSrvHeapIndex = -1;

    // Index into SRV heap for normal texture.
    int NormalSrvHeapIndex = -1;

    // Dirty flag indicating the material has changed and we need to update the constant buffer.
    // Because we have a material constant buffer for each FrameResource, we have to apply the
    // update to each FrameResource.  Thus, when we modify a material we should set 
    // NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
    int NumFramesDirty = 3; //gNumFrameResources

    // Material constant buffer data used for shading.
    DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
    DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
    float Roughness = .25f;
    DirectX::XMFLOAT4X4 MatTransform = MathHelper::Identity4x4();
};

struct RenderItem
{
    RenderItem() = default;

    // World matrix of the shape that describes the object's local space
    // relative to the world space, which defines the position, orientation,
    // and scale of the object in the world.
    XMFLOAT4X4 World = MathHelper::Identity4x4();

    XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

    // Dirty flag indicating the object data has changed and we need to update the constant buffer.
    // Because we have an object cbuffer for each FrameResource, we have to apply the
    // update to each FrameResource.  Thus, when we modify obect data we should set 
    // NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
    int NumFramesDirty = 3; //gNumFrameResources

    // Index into GPU constant buffer corresponding to the ObjectCB for this render item.
    UINT ObjCBIndex = -1;

    Material* Mat = nullptr;
    MeshGeometry* Geo = nullptr;

    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // DrawIndexedInstanced parameters.
    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;
};


class SleepyEngine
{
public:
    SleepyEngine(HINSTANCE hInstance);
    int Initialize();
    int Run();

    // GETTERS / SETTERS
    D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView()const; 
    ID3D12Resource* GetCurrentBackBuffer()const;
    D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView()const;

    LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static SleepyEngine* GetApp();

    void SetRessourceAllocator(RessourceAllocator* allocator);

    void Release();

private:
    void InitWindow(int nCmdShow);
    ATOM RegisterWindowClass();

    void FlushCommandQueue();
    void Draw();
    void DrawBis();
    void Update();

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

    void OnKeyboardInput(Timer& time);

    // D3DX12 Initialization
    void InitD3D();
    void EnableAdditionalD3D12Debug();
    void LoadTextures();
    void BuildMaterials();
    void BuildRenderItems();
    void CreateDevice();
    void CreateFence();
    void RecoverDescriptorsSize();
    void Check4xMSAAQualitySupport();
    void CreateCommandObjects();
    void CreateSwapChain();
    void CreateDescriptorHeaps();
    void CreateRenderTargetView();
    void CreateDepthStencilView();
    void SetViewport();
    void SetScissorRect();
    void BuildDescriptorHeaps();
    void BuildConstantBuffers();
    void BuildBoxGeometry();
    void BuildBoxGeometryBis();


private:
    WCHAR m_szTitle[MAX_LOADSTRING] = L"";                  // The title bar text
    WCHAR m_szWindowClass[MAX_LOADSTRING] = L"";            // the main window class name

    ID3D12Device* m_pDevice = nullptr;
    ID3D12Fence* m_pFence = nullptr;
    UINT64 m_currentFence = 0;

    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
    std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
    // List of all the render items.
    std::vector<std::unique_ptr<RenderItem>> mAllRitems;
    // Render items divided by PSO.
    std::vector<RenderItem*> mOpaqueRitems;

    UINT m_rtvDescriptorSize = 0;
    UINT m_dsvDescriptorSize = 0;
    UINT m_cbvSrvUavDescriptorSize = 0;

    ID3D12DescriptorHeap* m_pRtvHeap = nullptr;
    ID3D12DescriptorHeap* m_pDsvHeap = nullptr;

    DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    int m_currentBackBufferOffset = 0;

    D3D12_VIEWPORT* m_pViewPort = new D3D12_VIEWPORT();

    Camera m_Camera;

    UINT m_4xMsaaQuality = 0;
    bool m_4xMsaaState = false;

    ID3D12Resource* m_pDepthStencilBuffer = nullptr;

    ID3D12CommandQueue* m_pCommandQueue = nullptr;
    ID3D12CommandAllocator* m_pDirectCmdListAlloc = nullptr;
    ID3D12GraphicsCommandList* m_pCommandList = nullptr;

    IDXGIFactory4* m_pDxgiFactory = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr;
    ID3D12Resource* m_pSwapChainBuffer[SWAP_CHAIN_BUFFER_COUNT] = {nullptr, nullptr};

    ID3D12PipelineState* m_PSO = nullptr;
    ID3D12RootSignature* m_pRootSignature = nullptr;

    int m_clientWidth = 600;
    int m_clientHeight = 600;

    tagRECT m_scissorRect;

    HWND mhMainWnd = nullptr;
    HINSTANCE m_hAppInstance = nullptr;

    // To delete/Refactor: 
    ID3D12DescriptorHeap* m_pCbvHeap = nullptr;
    UploadBuffer<ObjectConstants>* m_pObjectCB = nullptr;
    XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    float mTheta = 1.5f * XM_PI;
    float mPhi = XM_PIDIV4;
    float mRadius = 5.0f;

    Mesh* mBoxGeo = nullptr;
    MeshGeometry* mBoxGeoBis = nullptr;
    Transform* m_Transform = nullptr;

    float xS = 0.5f;
    float yS = 0.5f;
    float zS = 0.5f;

    POINT m_LastMousePos;

    static SleepyEngine* m_App;

    RessourceAllocator* m_pAllocator;
};