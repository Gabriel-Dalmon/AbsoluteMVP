// SleepyEngine.cpp : Defines the entry point for the application.
//
#include "pch.h"

#include "resource.h"
//#include "UploadBuffer.h"
//#include "Utils/HResultException.h"
//#include "PSO.h"
//#include "tmpMeshGeo.h"

//#include "Camera.h"
//#include "Transform.h"
//#include "Mesh.h"
//#include "Shader.h"
//#include "Input.h"
//#include "Timer.h"
// 
//#include "SleepyEngine.h"

std::ostream& XM_CALLCONV operator<<(std::ostream& os, FXMVECTOR v)
{
    XMFLOAT3 dest;
    XMStoreFloat3(&dest, v);

    os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ")";
    return os;
}

std::ostream& XM_CALLCONV operator << (std::ostream& os, FXMMATRIX m)
{
    for (int i = 0; i < 4; ++i)
    {
        os << XMVectorGetX(m.r[i]) << "\t";
        os << XMVectorGetY(m.r[i]) << "\t";
        os << XMVectorGetZ(m.r[i]) << "\t";
        os << XMVectorGetW(m.r[i]);
        os << std::endl;
    }
    return os;
}

// Global Variables:

// Forward declarations of functions included in this code module:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

SleepyEngine::SleepyEngine(HINSTANCE hInstance)
{
    m_hAppInstance = hInstance;
}


void SleepyEngine::BlankInit()
{
}

void SleepyEngine::BlankUpdate()
{
}

void SleepyEngine::InitD3D()
{
#if defined(DEBUG) || defined(_DEBUG)
    EnableAdditionalD3D12Debug();
#endif
    CreateDevice();
    CreateFence();
    RecoverDescriptorsSize();
    Check4xMSAAQualitySupport();
    CreateCommandObjects();
    CreateSwapChain();
    CreateDescriptorHeaps();
    CreateRenderTargetView();
    ThrowIfFailed(m_pCommandList->Reset(m_pDirectCmdListAlloc, nullptr));
    CreateDepthStencilView();
    SetViewport();
    SetScissorRect();
    BuildDescriptorHeaps();
    BuildConstantBuffers();
    BuildBoxGeometry();
    

    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, static_cast<float>(m_clientWidth / m_clientHeight), 1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, P);
}

void SleepyEngine::EnableAdditionalD3D12Debug()
{
    ID3D12Debug* pDebugController;
    ThrowIfFailed(D3D12GetDebugInterface(__uuidof(ID3D12Debug), (void**)&pDebugController)); //should throw error
    pDebugController->EnableDebugLayer();
    std::cout << "Debug Layer Enabled" << std::endl;
}

void SleepyEngine::CreateDevice()
{
    ThrowIfFailed(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&m_pDxgiFactory));
    ThrowIfFailed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), (void**)&m_pDevice));
    //if failed, check book for "WARP_Adapters".
}

void SleepyEngine::CreateFence()
{
    ThrowIfFailed(m_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&m_pFence));
}

void SleepyEngine::RecoverDescriptorsSize()
{
    m_rtvDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    m_dsvDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
    m_cbvSrvUavDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void SleepyEngine::Check4xMSAAQualitySupport()
{
    D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels; //will likely be moved to private member attribute
    msQualityLevels.Format = m_backBufferFormat;
    msQualityLevels.SampleCount = 4;
    msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
    msQualityLevels.NumQualityLevels = 0;
    ThrowIfFailed(m_pDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels)));
    m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
    assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
}

void SleepyEngine::CreateCommandObjects()
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ThrowIfFailed(m_pDevice->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&m_pCommandQueue));
    ThrowIfFailed(m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_pDirectCmdListAlloc));
    ThrowIfFailed(m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pDirectCmdListAlloc, nullptr, __uuidof(ID3D12CommandList), (void**)&m_pCommandList));
    
    // Start off in a closed state. This is because the first time we 
    // refer to the command list we will Reset it, and it needs to be 
    // closed before calling Reset.

    ThrowIfFailed(m_pCommandList->Close()); 
}

void SleepyEngine::CreateSwapChain()
{
    delete m_pSwapChain;
    DXGI_SWAP_CHAIN_DESC swapChainDescriptor;
    swapChainDescriptor.BufferDesc.Width = m_clientWidth;
    swapChainDescriptor.BufferDesc.Height = m_clientHeight;
    swapChainDescriptor.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescriptor.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescriptor.BufferDesc.Format = m_backBufferFormat;
    swapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDescriptor.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
    swapChainDescriptor.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
    swapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescriptor.BufferCount = SWAP_CHAIN_BUFFER_COUNT;
    swapChainDescriptor.OutputWindow = mhMainWnd;
    swapChainDescriptor.Windowed = true;
    swapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ThrowIfFailed(m_pDxgiFactory->CreateSwapChain(m_pCommandQueue, &swapChainDescriptor, &m_pSwapChain)); //CreateSwapChainForHwnd()
}

void SleepyEngine::CreateDescriptorHeaps()
{
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
    rtvHeapDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    rtvHeapDesc.NodeMask = 0;
    ThrowIfFailed(m_pDevice->CreateDescriptorHeap(&rtvHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pRtvHeap));

    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    dsvHeapDesc.NodeMask = 0;
    ThrowIfFailed(m_pDevice->CreateDescriptorHeap(&dsvHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pDsvHeap));
}

void SleepyEngine::CreateRenderTargetView()
{
    //ID3D12Resource* m_pSwapChainBuffer[SWAP_CHAIN_BUFFER_COUNT]; // must be freed when finished
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_pRtvHeap->GetCPUDescriptorHandleForHeapStart());

    for (UINT i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
    {
        ThrowIfFailed(m_pSwapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)&m_pSwapChainBuffer[i]));
        m_pDevice->CreateRenderTargetView(m_pSwapChainBuffer[i], nullptr, rtvHeapHandle);
        rtvHeapHandle.Offset(1, m_rtvDescriptorSize); 
    }
}

void SleepyEngine::CreateDepthStencilView()
{
    D3D12_RESOURCE_DESC depthStencilDesc;
    depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    depthStencilDesc.Alignment = 0;
    depthStencilDesc.Width = m_clientWidth;
    depthStencilDesc.Height = m_clientHeight;
    depthStencilDesc.DepthOrArraySize = 1;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
    depthStencilDesc.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
    depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    // Describes a value used to optimize clear operations for a particular resource.
    // https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_clear_value
    D3D12_CLEAR_VALUE optClear;
    optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    optClear.DepthStencil.Depth = 1.0f;
    optClear.DepthStencil.Stencil = 0;

    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
    ThrowIfFailed(m_pDevice->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &depthStencilDesc,
        D3D12_RESOURCE_STATE_COMMON,
        &optClear,
        __uuidof(ID3D12Resource),
        (void**)&m_pDepthStencilBuffer
    ));

    /*D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.Texture2D.MipSlice = 0;*/
    m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, nullptr, GetDepthStencilView()); //nullptr for default mip level 0

    CD3DX12_RESOURCE_BARRIER ressourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        m_pDepthStencilBuffer,
        D3D12_RESOURCE_STATE_COMMON,
        D3D12_RESOURCE_STATE_DEPTH_WRITE);
    m_pCommandList->ResourceBarrier(
        1,
        &ressourceBarrier
    );
}

void SleepyEngine::SetViewport()
{
    m_pViewPort->TopLeftX = 0.0f;
    m_pViewPort->TopLeftY = 0.0f;
    m_pViewPort->Width = static_cast<float>(m_clientWidth);
    m_pViewPort->Height = static_cast<float>(m_clientHeight);
    m_pViewPort->MinDepth = 0.0f;
    m_pViewPort->MaxDepth = 1.0f;
}

// Scissor rect is used to clip pixels to a certain area of the render target and avoid rendering them (ex: pixels below UI).
void SleepyEngine::SetScissorRect()
{
    m_scissorRect.left = 0;
    m_scissorRect.top = 0;
    m_scissorRect.right = m_clientWidth;
    m_scissorRect.bottom = m_clientHeight;
}

int SleepyEngine::Initialize()
{
    try
    {
        LoadStringW(m_hAppInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
        LoadStringW(m_hAppInstance, IDC_SLEEPYENGINE, m_szWindowClass, MAX_LOADSTRING);
        RegisterWindowClass();
        InitWindow(SW_SHOW);
        InitD3D();
        m_Camera.SetPosition(0.0f, 2.0f, -10.0f);
    }
    catch (HResultException error)
    {
        std::wstring messageBoxText;
        MessageBox(nullptr, error.ToString().c_str(), L"HRESULT ERROR", MB_OK);
    	HRESULT hr = m_pDevice->GetDeviceRemovedReason();
        if (FAILED(hr))
        {
            _com_error error(hr);
            std::string errorMessage = "Device Removed Reason:\n" + D3DUtils::HrToString(hr);
            MessageBoxA(nullptr, errorMessage.c_str(), "Device Removed", MB_OK | MB_ICONERROR);
            MessageBox(nullptr, error.ErrorMessage(),L"Device Removed", MB_OK);
        }
        return 1;
    }
    m_App = this;
    m_pAllocator = new RessourceAllocator;
    m_pAllocator->Init(m_pDevice, m_pCommandList);
    m_pFactory->Init(m_pAllocator);
    
    

    // close command list 
    m_pCommandList->Close();

    // execute command list
    ID3D12CommandList* cmdsLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // flush command list
    FlushCommandQueue();

#if defined (DEBUG) || (_DEBUG)
    CreateTexture(L"../SleepyEngine/src/asset/t_box.dds");
    CreateTexture(L"../SleepyEngine/src/asset/t_bricks.dds");
    CreateTexture(L"../SleepyEngine/src/asset/t_skybox.dds");
#else
    CreateTexture(L"asset/t_box.dds");
    CreateTexture(L"asset/t_bricks.dds");
    CreateTexture(L"asset/t_skybox.dds");
#endif
    BlankInit();

    return 0;
}


void SleepyEngine::BuildDescriptorHeaps()
{
    D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
    cbvHeapDesc.NumDescriptors = 25;
    cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    cbvHeapDesc.NodeMask = 0;
    ThrowIfFailed(m_pDevice->CreateDescriptorHeap(&cbvHeapDesc,
        IID_PPV_ARGS(&m_pCbvHeap)));
}

void SleepyEngine::BuildConstantBuffers()
{
    m_pObjectCB = new UploadBuffer<ObjectConstants>(m_pDevice, 1, true);

    //UINT objCBByteSize = ((sizeof(ObjectConstants) + 255) & ~255);
    //
    //D3D12_GPU_VIRTUAL_ADDRESS cbAddress = m_pObjectCB->Resource()->GetGPUVirtualAddress();
    //// Offset to the ith object constant buffer in the buffer.
    //int boxCBufIndex = 0;
    //cbAddress += boxCBufIndex * objCBByteSize;
    //
    //D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
    //cbvDesc.BufferLocation = cbAddress;
    //cbvDesc.SizeInBytes = ((sizeof(ObjectConstants) + 255) & ~255);
    //
    //m_pDevice->CreateConstantBufferView(
    //    &cbvDesc,
    //    m_pCbvHeap->GetCPUDescriptorHandleForHeapStart());


}

int SleepyEngine::Run()
{
    m_Transform = new Transform();
    m_Transform->Identity();  
    m_Transform->SetScale(.5f, .5f, .5f);

    HACCEL hAccelTable = LoadAccelerators(m_hAppInstance, MAKEINTRESOURCE(IDC_SLEEPYENGINE));

    MSG msg = { 0 };

    Input input;
    input.Init();

    Timer timer;
    timer.Init();

    
    // We setup PSO and load shader for textures
    ShaderTexture shaderTexture;
    shaderTexture.Init();
    ThrowIfFailed(m_pDevice->CreateRootSignature(
        0,
        shaderTexture.m_pSerializedRootSig->GetBufferPointer(),
        shaderTexture.m_pSerializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(&m_pRootSignatureTexture))
    );

#if defined (DEBUG) || (_DEBUG)
    shaderTexture.CompileVS(L"../SleepyEngine/src/shaders/Texture.hlsl");
    shaderTexture.CompilePS(L"../SleepyEngine/src/shaders/Texture.hlsl");
#else
    shaderTexture.CompileVS(L"Shaders/Texture.hlsl");
    shaderTexture.CompilePS(L"Shaders/Texture.hlsl");
#endif

    m_PSOTexture = InitPSO(shaderTexture.m_pInputLayout, m_pRootSignatureTexture, shaderTexture.m_pVSByteCode, shaderTexture.m_pPSByteCode, m_backBufferFormat, false, 0,
        DXGI_FORMAT_D24_UNORM_S8_UINT, m_pDevice, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);


    // We setup PSO and load shader for Color
    ShaderColor shaderColor;
    shaderColor.Init();
    ThrowIfFailed(m_pDevice->CreateRootSignature(
        0,
        shaderColor.m_pSerializedRootSig->GetBufferPointer(),
        shaderColor.m_pSerializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(&m_pRootSignatureColor))
    );

#if defined (DEBUG) || (_DEBUG)
    shaderColor.CompileVS(L"../SleepyEngine/src/shaders/Color.hlsl");
    shaderColor.CompilePS(L"../SleepyEngine/src/shaders/Color.hlsl");
#else
    shaderColor.CompileVS(L"Shaders/Color.hlsl");
    shaderColor.CompilePS(L"Shaders/Color.hlsl");
#endif

    m_PSOColor = InitPSO(shaderColor.m_pInputLayout, m_pRootSignatureColor, shaderColor.m_pVSByteCode, shaderColor.m_pPSByteCode, m_backBufferFormat, false, 0,
        DXGI_FORMAT_D24_UNORM_S8_UINT, m_pDevice, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);

    m_pFactory->SetSignatureAndPSO(this);

    m_pDirectCmdListAlloc->Reset();
    m_pCommandList->Reset(m_pDirectCmdListAlloc, nullptr);

    BuildBoxGeometryBis();
    BlankPreLoop();

    m_pCommandList->Close();
    ID3D12CommandList* cmdsLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
    FlushCommandQueue();



    // Main message loop:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
        /*if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {*/
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            //std::cout << m_Camera.GetPosition() << std::endl;
            //std::cout << m_Camera.GetView() << std::endl;
            timer.UpdateTimer();

            input.Update();

            timer.UpdateFPS(mhMainWnd);

            //for (Entity* entity : m_entities) {
            //for (int i = 0; i < m_entities.size(); i++) {
            //    if (m_entities[i]->GetComponent<Script*>() != nullptr) {
            //        m_entities[i]->GetComponent<Script*>()->OnScript();
            //        m_entities[i]->GetComponent<Transform*>()->Update();

            //        XMMATRIX view = m_Camera.GetView();
            //        XMMATRIX world = XMLoadFloat4x4(&m_entities[i]->GetComponent<Transform*>()->m_transformMatrix);
            //        XMMATRIX proj = m_Camera.GetProj();
            //        XMMATRIX worldViewProj = world * view * proj;

            //        // Update the constant buffer with the latest worldViewProj matrix.
            //        ObjectConstants objConstants;
            //        XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
            //        m_pObjectCB->CopyData(i+1, objConstants);
            //    }
            //}

            OnKeyboardInput(timer);
            Update();
            DrawBis();
            BlankUpdate();
        }
        
    }
    Release();
    shaderTexture.Release();
    shaderColor.Release();

    return (int)msg.wParam;
}

D3D12_CPU_DESCRIPTOR_HANDLE SleepyEngine::GetCurrentBackBufferView()const
{
    // CD3DX12 constructor to offset to the RTV of the current back buffer.
    return CD3DX12_CPU_DESCRIPTOR_HANDLE(
        m_pRtvHeap->GetCPUDescriptorHandleForHeapStart(),// handle start
        m_currentBackBufferOffset, // index to offset
        m_rtvDescriptorSize); // byte size of descriptor
}

ID3D12Resource* SleepyEngine::GetCurrentBackBuffer()const
{
    return m_pSwapChainBuffer[m_currentBackBufferOffset];
}

D3D12_CPU_DESCRIPTOR_HANDLE SleepyEngine::GetDepthStencilView()const
{
    return m_pDsvHeap->GetCPUDescriptorHandleForHeapStart();
}

void SleepyEngine::Release()
{
    // Variables membres avec une méthode Release, et membres DirectX
    RELEASE(m_pDevice);
    RELEASE(m_pFence);
    RELEASE(m_pRtvHeap);
    RELEASE(m_pDsvHeap);
    RELEASE(m_pDepthStencilBuffer);
    RELEASE(m_pCommandQueue);
    RELEASE(m_pDirectCmdListAlloc);
    RELEASE(m_pCommandList);
    RELEASE(m_pDxgiFactory);
    RELEASE(m_pSwapChain);
    RELEASE(m_PSOTexture);
    RELEASE(m_pRootSignatureTexture);
    RELEASE(m_PSOColor);
    RELEASE(m_pRootSignatureColor);
    RELEASE(m_pCbvHeap);
    RELEASE(mBoxGeo);
    RELEASE(m_pAllocator);
    
    // "new"
    DELETE(m_pViewPort);
    DELETE(m_pObjectCB);
    DELETE(m_Transform);
    DELETE(mBoxGeo);
    DELETE(mBoxGeoBis);

    // Window and Window Class
    DestroyWindow(mhMainWnd); 
    UnregisterClassW(m_szWindowClass, m_hAppInstance);
}

ATOM SleepyEngine::RegisterWindowClass()
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hAppInstance;
    wcex.hIcon = LoadIcon(m_hAppInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = m_szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

void SleepyEngine::InitWindow(int nCmdShow)
{
    mhMainWnd = CreateWindow(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_clientWidth, m_clientHeight, 0, 0, m_hAppInstance, 0);

    if (mhMainWnd == NULL)
    {
        MessageBox(0, L"CreateWindow FAILED", 0, 0);
        return;
    }
    ShowWindow(mhMainWnd, nCmdShow);
    UpdateWindow(mhMainWnd);

}

SleepyEngine* SleepyEngine::m_App = nullptr;
SleepyEngine* SleepyEngine::GetApp()
{
    return m_App;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return SleepyEngine::GetApp()->MsgProc(hWnd, message, wParam, lParam);
}

LRESULT SleepyEngine::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
            /*case IDM_ABOUT:
                DialogBox((HINSTANCE)wParam, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;*/
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
        OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
        OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    case WM_MOUSEMOVE:
        OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void SleepyEngine::FlushCommandQueue()
{
    // Advance the fence value to mark commands up to this fence point.
    m_currentFence++;

    // Add an instruction to the command queue to set a new fence point.  Because we 
    // are on the GPU timeline, the new fence point won't be set until the GPU finishes
    // processing all the commands prior to this Signal().
    ThrowIfFailed(m_pCommandQueue->Signal(m_pFence, m_currentFence));

    // Wait until the GPU has completed commands up to this fence point.
    if (m_pFence->GetCompletedValue() < m_currentFence)
    {
        HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);

        // Fire event when GPU hits current fence.  
        ThrowIfFailed(m_pFence->SetEventOnCompletion(m_currentFence, eventHandle));

        // Wait until the GPU hits current fence event is fired.
        if (eventHandle != 0)
        {
            WaitForSingleObject(eventHandle, INFINITE);
            CloseHandle(eventHandle); 
        }
    }
}

void SleepyEngine::BuildBoxGeometry()
{
}

void SleepyEngine::BuildBoxGeometryBis()
{
    //mBoxGeo = m_pAllocator->getMesh("pyramide");
    /*Entity* player = Entity::CreateEmptyEntity();
    m_pFactory->FillPlayer(player);
    m_entities.push_back(player);
    MeshRenderer* temp;
    temp = player->GetComponent<MeshRenderer*>();
    mBoxGeo = temp->GetMesh();*/
}


void SleepyEngine::Update()
{
    //std::cout << "Update" << std::endl;
    // Convert Spherical to Cartesian coordinates.
    float x = mRadius * sinf(mPhi) * cosf(mTheta); 
    float z = mRadius * sinf(mPhi) * sinf(mTheta); 
    float y = mRadius * cosf(mPhi); 

    // Build the view matrix.
    XMVECTOR pos = XMVectorSet(x, y, z, 1.0f); 
    XMVECTOR target = XMVectorZero(); 
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); 

    //XMMATRIX view = XMMatrixLookAtLH(pos, target, up); 
    //XMStoreFloat4x4(&mView, view); 
    XMMATRIX view = m_Camera.GetView();
    XMStoreFloat4x4(&mView, view);

    // Rotation essai 0:
    // m_Transform.Identity();
    //m_Transform->Rotate(.001f, .001f, .001f);
    if (xS <= 1.f /*&& yS <= 1.f && zS <= 1.f*/)
    {
        xS += 0.005;
        /*yS += 0.005;
        zS += 0.005;*/
        m_Transform->SetScale(xS, yS, zS);
        //std::cout << m_Transform->m_scaleVect.x << std::endl;
    }
    float xC = XMVectorGetX(m_Camera.GetPosition());  
    float yC = XMVectorGetY(m_Camera.GetPosition());  
    float zC = XMVectorGetZ(m_Camera.GetPosition());  
     
    //m_Transform->LookAt(xC, yC, zC);

    

    XMMATRIX world = XMLoadFloat4x4(&m_Transform->m_transformMatrix);
    //XMMATRIX proj = XMLoadFloat4x4(&mProj);
    XMMATRIX proj = m_Camera.GetProj();
    XMMATRIX worldViewProj = world * view * proj;

    // Update the constant buffer with the latest worldViewProj matrix.
    ObjectConstants objConstants;
    XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
    m_pObjectCB->CopyData(0, objConstants);

    //m_CBindex = 0;
    //for (Entity* entity : m_entities) {
    //    if (entity->GetComponent<Script*>() != nullptr) {
    //        ++m_CBindex;
    //        entity->GetComponent<Script*>()->OnScript();
    //        entity->GetComponent<Transform*>()->Update();

    //        world = XMLoadFloat4x4(&entity->GetComponent<Transform*>()->m_transformMatrix);
    //        worldViewProj = world * view * proj;

    //        // Update the constant buffer with the latest worldViewProj matrix.
    //        XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
    //        m_pObjectCB->CopyData(m_CBindex, objConstants);
    //    }
    }
}

//void SleepyEngine::Draw(ID3D12DescriptorHeap* pCBVHeap, ID3D12RootSignature* pRootSignature, Mesh* mesh)
void SleepyEngine::Draw()
{
}


void SleepyEngine::DrawBis()
{
    CD3DX12_RESOURCE_BARRIER barrier;

    barrier = CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    D3D12_CPU_DESCRIPTOR_HANDLE currentBackBufferView = GetCurrentBackBufferView();
    D3D12_CPU_DESCRIPTOR_HANDLE dephtStencilView = GetDepthStencilView();

    m_pDirectCmdListAlloc->Reset();

    m_pCommandList->Reset(m_pDirectCmdListAlloc, nullptr);
    m_pCommandList->RSSetViewports(1, m_pViewPort);
    m_pCommandList->RSSetScissorRects(1, &m_scissorRect);

    m_pCommandList->ResourceBarrier(1, &barrier);

    m_pCommandList->ClearRenderTargetView(currentBackBufferView, Colors::LightSteelBlue, 0, nullptr);
    m_pCommandList->ClearDepthStencilView(dephtStencilView, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

    m_pCommandList->OMSetRenderTargets(1, &currentBackBufferView, true, &dephtStencilView);

    Mesh* mesh;
    ShaderReference* shaderRef;
    for (Entity* entity : m_entities)
    {
        mesh = entity->GetComponent<MeshRenderer*>()->GetMesh();
        shaderRef = entity->GetComponent<ShaderReference*>();


        ID3D12DescriptorHeap* descriptorHeaps[] = { m_pCbvHeap };
        m_pCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

        m_pCommandList->SetGraphicsRootSignature(shaderRef->GetRootSignature());//
        //m_pCommandList->SetGraphicsRootSignature(m_pRootSignatureTexture);

        m_pCommandList->SetPipelineState(shaderRef->GetPSO());//
        //m_pCommandList->SetPipelineState(m_PSOTexture);

        
        m_pCommandList->IASetVertexBuffers(0, 1, &mesh->VertexBufferView());
        m_pCommandList->IASetIndexBuffer(&mesh->IndexBufferView());
        m_pCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        

        if (shaderRef->GetPSO() == m_PSOTexture) {
            CD3DX12_GPU_DESCRIPTOR_HANDLE tex(m_pCbvHeap->GetGPUDescriptorHandleForHeapStart()); //
            tex.Offset(shaderRef->GetTexID(), m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)); //
            m_pCommandList->SetGraphicsRootDescriptorTable(0, tex); //
            m_pCommandList->SetGraphicsRootConstantBufferView(1, m_pObjectCB->Resource()->GetGPUVirtualAddress());//
        }
        else if (shaderRef->GetPSO() == m_PSOColor) {
            m_pCommandList->SetGraphicsRootConstantBufferView(0, m_pObjectCB->Resource()->GetGPUVirtualAddress());//
        }


        m_pCommandList->DrawIndexedInstanced(mesh->m_drawArgs["box"].IndexCount, 1, mesh->m_drawArgs["box"].StartIndexLocation, mesh->m_drawArgs["box"].BaseVertexLocation, 0);
    }

    barrier = CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    m_pCommandList->ResourceBarrier(1, &barrier);

    m_pCommandList->Close();

    ID3D12CommandList* cmdsLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    ThrowIfFailed(m_pSwapChain->Present(0, 0));
    m_currentBackBufferOffset = (m_currentBackBufferOffset + 1) % SWAP_CHAIN_BUFFER_COUNT;
    FlushCommandQueue();
}

// Note: the best option is to remove that and make them callbacks with the input class
void SleepyEngine::OnMouseDown(WPARAM btnState, int x, int y)
{
    m_LastMousePos.x = x;
    m_LastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void SleepyEngine::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void SleepyEngine::OnMouseMove(WPARAM btnState, int x, int y)
{
    //std::cout << "Moov Boolet" << std::endl;
    if ((btnState & MK_LBUTTON) != 0)
    {
        //std::cout << "Cam" << std::endl;
        // Make each pixel correspond to a quarter of a degree.
        float dx = XMConvertToRadians(0.25f * static_cast<float>(x - m_LastMousePos.x));
        float dy = XMConvertToRadians(0.25f * static_cast<float>(y - m_LastMousePos.y));

        m_Camera.Pitch(dy);
        m_Camera.RotateY(dx);

        m_Camera.UpdateViewMatrix();
    }

    m_LastMousePos.x = x;
    m_LastMousePos.y = y;
}

void SleepyEngine::OnKeyboardInput(Timer& timer)
{
    const float dt = timer.GetDeltaTime();

    if (GetAsyncKeyState('Z') & 0x8000)
        m_Camera.Walk(5.0f * dt);

    if (GetAsyncKeyState('S') & 0x8000)
        m_Camera.Walk(-5.0f * dt);

    if (GetAsyncKeyState('Q') & 0x8000)
        m_Camera.Strafe(-5.0f * dt);

    if (GetAsyncKeyState('D') & 0x8000)
        m_Camera.Strafe(5.0f * dt);

    m_Camera.UpdateViewMatrix();
}

void SleepyEngine::SetRessourceAllocator(RessourceAllocator* allocator)
{
    m_pAllocator = allocator;
}

void SleepyEngine::SetFactory(Factory* factory)
{
    m_pFactory = factory;
}

void SleepyEngine::CreateTexture(const wchar_t* fileName)
{
    // reset command list
    m_pDirectCmdListAlloc->Reset();
    m_pCommandList->Reset(m_pDirectCmdListAlloc, nullptr);

    // init variables textures 
    Microsoft::WRL::ComPtr<ID3D12Resource> texture;
    Microsoft::WRL::ComPtr<ID3D12Resource> textureUpload;

    // on load la texture ddsdepuis son emplacment de fichier
    ThrowIfFailed(CreateDDSTextureFromFile12(m_pDevice, m_pCommandList, fileName, texture, textureUpload));

    // créer un SRV Descriptors 
    CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(m_pCbvHeap->GetCPUDescriptorHandleForHeapStart());

    // Pour trouver la taille d'une case du heap pour l'offset ici = 32
    //std::cout << "size d'une case du heap :" << m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) << std::endl;

    // On decale d'une case dans le heap ( une case = 32 octets )
    hDescriptor.Offset(m_textureIndex, m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    m_textureIndex = m_textureIndex + 1;

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = texture->GetDesc().Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = texture->GetDesc().MipLevels;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
    m_pDevice->CreateShaderResourceView(texture.Get(), &srvDesc, hDescriptor);


    // close command list 
    m_pCommandList->Close();

    // execute command list
    ID3D12CommandList* cmdsLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // flush command list
    FlushCommandQueue();

    // get and need to store texture

    //ID3D12Resource* pTexture = texture.Get();
    m_Texture = texture.Get();

    texture.Detach();
}

ID3D12PipelineState* SleepyEngine::GetPSOTexture() {
    return m_PSOTexture;
}

ID3D12PipelineState* SleepyEngine::GetPSOColor() {
    return m_PSOColor;
}

ID3D12RootSignature* SleepyEngine::GetRootSignatureTexture() {
    return m_pRootSignatureTexture;
}

ID3D12RootSignature* SleepyEngine::GetRootSignatureColor() {
    return m_pRootSignatureColor;
}