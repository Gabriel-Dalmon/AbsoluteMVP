#include "pch.h"

Mesh::Mesh() {}

Mesh::~Mesh() {}

// Should pass a mesh descriptor instead
void Mesh::Initialize(int vertexByteStride, int vertexBufferByteSize, unsigned int indexCount, int indexBufferByteSize, ID3DBlob* pCPUVertexBuffer, ID3DBlob* pCPUIndexBuffer, ID3D12Resource* pGPUVertexBuffer, ID3D12Resource* pGPUIndexBuffer)
{
	m_vertexByteStride = vertexByteStride;
	m_vertexBufferByteSize = vertexBufferByteSize;
	m_indexCount = indexCount;
	m_indexBufferByteSize = indexBufferByteSize;
	m_CPUVertexBuffer = pCPUVertexBuffer;
	m_CPUIndexBuffer = pCPUIndexBuffer;
	m_pGPUVertexBuffer = pGPUVertexBuffer;
	m_pGPUIndexBuffer = pGPUIndexBuffer;

	m_startIndexLocation = 0;
	m_baseVertexLocation = 0;
}

void Mesh::Release()
{
	RELEASE(m_pEntity);
	RELEASE(m_pGPUIndexBuffer);
	RELEASE(m_pGPUVertexBuffer);
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