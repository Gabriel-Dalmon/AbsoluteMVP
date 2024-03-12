#pragma once

class FrameResource
{
public:
	FrameResource();
	~FrameResource();

	void Initialize(ID3D12Device* pDevice);
	void CleanUp();

	// GETTERS & SETTERS
	unsigned __int64 GetFence() const { return m_currentFence; }
	inline void IncrementFence() { m_currentFence++;  };

private:
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;
	unsigned __int64 m_currentFence = 0;

	// Constant Buffers
};