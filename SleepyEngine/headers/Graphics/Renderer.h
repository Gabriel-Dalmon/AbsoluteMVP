#pragma once


#ifndef _WINDEF_
class HINSTANCE__; // Forward or never
typedef HINSTANCE__* HINSTANCE;
#endif

class Device;
class SwapChain;
class Window;
class CommandQueue;
class IDXGIFactory4;
class ID3D12RootSignature;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(HINSTANCE hInstance, int windowWidth, int windowHeight);
	void BuildRootSignature();
	void RenderFrame();
	void CleanUp();

private:
	Window* m_pWindow = nullptr;

	IDXGIFactory4* m_pDxgiFactory = nullptr;
	Device* m_pDevice = nullptr;
	SwapChain* m_pSwapChain = nullptr;
	ID3D12RootSignature* m_pRootSignature = nullptr;

	CommandQueue* m_pCommandQueue = nullptr;
	ID3D12GraphicsCommandList* m_pCommandList = nullptr;
};