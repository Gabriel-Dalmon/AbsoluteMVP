#include "pch.h"

FrameResource::FrameResource(Device* pDevice, UINT objectCount)
{
	m_entitiesConstantsBuffers = new UploadBuffer<EntityConstants>(pDevice->GetD3DDevice(), objectCount, true);
}

FrameResource::~FrameResource()
{
}

void FrameResource::Initialize(ID3D12Device* pDevice)
{
	pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_pCommandAllocator);
}

void FrameResource::Release()
{
	if (m_pCommandAllocator)
	{
		m_pCommandAllocator->Release();
		m_pCommandAllocator = nullptr;
	}
}
