#pragma once

class FrameResource
{
public:
	FrameResource();
	~FrameResource();

	void Initialize(ID3D12Device* pDevice);
	void CleanUp();

private:
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;
	// Constant buffers
	unsigned __int64 m_fence = 0;
};