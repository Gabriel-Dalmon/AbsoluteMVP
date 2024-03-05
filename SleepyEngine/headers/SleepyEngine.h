#pragma once

#include "resource.h"

#include "d3dx12.h"
#include <dxgi1_4.h>
#include "MathHelper.h"
#include "UploadBuffer.h"


#define MAX_LOADSTRING 100
#define SWAP_CHAIN_BUFFER_COUNT 2

class Mesh;
class MeshGeometry;

struct ObjectConstants
{
    DirectX::XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
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

    void Release();

private:
    void InitWindow(int nCmdShow);
    ATOM RegisterWindowClass();

    void FlushCommandQueue();
    void Draw();
    void DrawBis();
    void Update();

    // D3DX12 Initialization
    void InitD3D();
    void EnableAdditionalD3D12Debug();
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
    WCHAR m_szTitle[MAX_LOADSTRING];                  // The title bar text
    WCHAR m_szWindowClass[MAX_LOADSTRING];            // the main window class name

    ID3D12Device* m_pDevice = nullptr;

    ID3D12Fence* m_pFence = nullptr;
    UINT64 m_currentFence = 0;

    UINT m_rtvDescriptorSize = 0;
    UINT m_dsvDescriptorSize = 0;
    UINT m_cbvSrvUavDescriptorSize = 0;

    ID3D12DescriptorHeap* m_pRtvHeap = nullptr;
    ID3D12DescriptorHeap* m_pDsvHeap = nullptr;

    DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    int m_currentBackBufferOffset = 0;

    D3D12_VIEWPORT* m_pViewPort = new D3D12_VIEWPORT();

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
    DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    float mTheta = 1.5f * DirectX::XM_PI;
    float mPhi = DirectX::XM_PIDIV4;
    float mRadius = 5.0f;

    Mesh* mBoxGeo = nullptr;
    MeshGeometry* mBoxGeoBis = nullptr;
};