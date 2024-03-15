#include "pch.h"

CommandQueue::CommandQueue()
{
}

CommandQueue::~CommandQueue()
{
}

int CommandQueue::Initialize(Device* pDevice)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ThrowIfFailed(pDevice->GetD3DDevice()->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&m_pD3DCommandQueue));
    ThrowIfFailed(pDevice->GetD3DDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&m_pFence));
	return 0;
}

void CommandQueue::Execute(unsigned int commandsListsCount, ID3D12CommandList* const commandsLists[])
{
    m_pD3DCommandQueue->ExecuteCommandLists(commandsListsCount, commandsLists);
}

void CommandQueue::Signal(UINT64 currentFence)
{
    m_pD3DCommandQueue->Signal(m_pFence, currentFence);
}

void CommandQueue::Flush()
{
    m_currentFence++;
    ThrowIfFailed(m_pD3DCommandQueue->Signal(m_pFence, m_currentFence));
    UINT64 fen = m_pFence->GetCompletedValue();
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

int CommandQueue::Release()
{
    return 0;
}

HRESULT CommandQueue::SetEventOnFenceCompletion(UINT64 currentFence, HANDLE eventHandle)
{
    return m_pFence->SetEventOnCompletion(currentFence, eventHandle);
}

