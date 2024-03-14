#pragma once

struct EntityConstants
{
	XMFLOAT4X4 transformMatrix = MathHelper::Identity4x4();
};

class FrameResource
{
public:
	FrameResource();
	~FrameResource();

	void Initialize(ID3D12Device* pDevice);
	void Release();

	inline HRESULT ResetCommandAllocator() { return m_pCommandAllocator->Reset(); };

	// GETTERS & SETTERS
	UINT64 GetFence() const { return m_currentFence; }
	inline void IncrementFence() { ++m_currentFence;  };
	inline void SetFence(UINT64 fence) { m_currentFence = fence; }
	inline ID3D12CommandAllocator* GetD3DCommandAllocator()const { return m_pCommandAllocator; };
	inline UploadBuffer<EntityConstants>* GetEntitiesConstantsBuffers()const { return EntitiesConstantsBuffers; };

private:
	ID3D12CommandAllocator* m_pCommandAllocator = nullptr;
	UINT64 m_currentFence = 0;

	// Constant Buffers
	//UploadBuffer<PassConstants>* PassCB = nullptr;
	UploadBuffer<EntityConstants>* EntitiesConstantsBuffers = nullptr;
};