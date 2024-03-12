#pragma once

class CommandQueue
{
public:
	CommandQueue();
	~CommandQueue();

	int Initialize(Device* pDevice);
	void Execute(unsigned int commandsListsCount, ID3D12CommandList* const commandsLists[]);
	void Signal(UINT currentFence);
	void Flush();
	int Release();

	// Getters
	ID3D12CommandQueue* GetD3DCommandQueue() const { return m_pD3DCommandQueue; }

	inline UINT GetLastCompletedFence()const { return m_currentFence; };
	HRESULT SetEventOnFenceCompletion(UINT currentFence, HANDLE eventHandle);

private:
	ID3D12CommandQueue* m_pD3DCommandQueue = nullptr;
	ID3D12Fence* m_pFence = nullptr;
	UINT m_currentFence;
};