#include "Graphics/FrameResource.h"

#include <d3d12.h>

FrameResource::FrameResource()
{
}

FrameResource::~FrameResource()
{
}

void FrameResource::Initialize(ID3D12Device* pDevice)
{
	pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_pCommandAllocator);
}

void FrameResource::CleanUp()
{
	if (m_pCommandAllocator)
	{
		m_pCommandAllocator->Release();
		m_pCommandAllocator = nullptr;
	}
}
