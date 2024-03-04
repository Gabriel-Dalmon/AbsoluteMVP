#include "Graphics/CommandQueue.h"
#include "Graphics/Device.h"

#include "Utils/HResultException.h"

#include "d3dx12.h"


int CommandQueue::Initialize(Device* pDevice)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    ThrowIfFailed(pDevice->GetD3DDevice()->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&m_pD3DCommandQueue));
	return 0;
}
