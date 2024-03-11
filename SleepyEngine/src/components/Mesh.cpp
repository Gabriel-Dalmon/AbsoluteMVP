#include "pch.h"

Mesh::Mesh() {}

Mesh::~Mesh() {}

void Mesh::Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<uint16_t>* indices)
{
	m_vertexByteStride = sizeof(Vertex);
	m_vertexBufferByteSize = sizeof(Vertex) * vertices->size();
	m_indexCount = indices->size();
	m_indexBufferByteSize = sizeof(uint16_t) * m_indexCount;
	std::cout << "Index BSize" << m_indexBufferByteSize << std::endl;
	
	m_pGPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices, m_vertexBufferByteSize, m_pUploaderVertexBuffer);
	m_pGPUIndexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices, m_indexBufferByteSize, m_pUploaderIndexBuffer);
}

void Mesh::Release()
{
	RELEASE(m_pEntity);
	RELEASE(m_pGPUIndexBuffer);
	RELEASE(m_pGPUVertexBuffer);
	RELEASE(m_pUploaderIndexBuffer);
	RELEASE(m_pUploaderVertexBuffer);
}


D3D12_VERTEX_BUFFER_VIEW Mesh::VertexBufferView()const
{
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = m_pGPUVertexBuffer->GetGPUVirtualAddress();
	vbv.StrideInBytes = m_vertexByteStride;
	vbv.SizeInBytes = m_vertexBufferByteSize;

	return vbv;
}


D3D12_INDEX_BUFFER_VIEW Mesh::IndexBufferView()const
{
	D3D12_INDEX_BUFFER_VIEW ibv;
	ibv.BufferLocation = m_pGPUIndexBuffer->GetGPUVirtualAddress();
	ibv.Format = IndexFormat;
	ibv.SizeInBytes = m_indexBufferByteSize;

	return ibv;
}



//D3D12_RESOURCE_DESC