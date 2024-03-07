#include "pch.h"
#include "Graphics/CommandQueue.h"
#include "Graphics/Device.h"

#include "Utils/HResultException.h"


int CommandQueue::Initialize(Device* pDevice)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ThrowIfFailed(pDevice->GetD3DDevice()->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&m_pD3DCommandQueue));
	return 0;
}

void CommandQueue::Execute(unsigned int commandsListsCount, ID3D12CommandList* const commandsLists[])
{
    m_pD3DCommandQueue->ExecuteCommandLists(commandsListsCount, commandsLists);
}

void CommandQueue::Flush()
{
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
