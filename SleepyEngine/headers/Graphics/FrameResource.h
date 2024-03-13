#pragma once

class FrameResource
{
public:
	FrameResource();
	~FrameResource();

	void Initialize(ID3D12Device* pDevice);
	void Release();

	inline void ResetCommandAllocator() { m_pCommandAllocator->Reset(); };

	// GETTERS & SETTERS
	unsigned __int64 GetFence() const { return m_currentFence; }
	inline void IncrementFence() { m_currentFence++;  };
	inline ID3D12CommandAllocator* GetD3DCommandAllocator()const { return m_pCommandAllocator; }

private:
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;
	unsigned __int64 m_currentFence = 0;

	// Constant Buffers
};