#include <vector>

#include "Transform.h"
#include "Mesh.h"
#include "D3DUtils.h"

Mesh::Mesh() {}

Mesh::~Mesh() {}

void Mesh::Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<int>* indices)
{
	m_vertexByteStride = sizeof(Vertex);
	m_vertexBufferByteSize = sizeof(Vertex) * vertices->size();
	m_indexCount = indices->size();
	m_indexBufferByteSize = sizeof(Vertex) * m_indexCount;
	
	m_GPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices, m_vertexBufferByteSize, m_uploaderVertexBuffer);
	m_GPUIndexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices, m_indexBufferByteSize, m_uploaderIndexBuffer);
}


D3D12_VERTEX_BUFFER_VIEW Mesh::VertexBufferView()const
{
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = m_GPUVertexBuffer->GetGPUVirtualAddress();
	vbv.StrideInBytes = m_vertexByteStride;
	vbv.SizeInBytes = m_vertexBufferByteSize;

	return vbv;
}


D3D12_INDEX_BUFFER_VIEW Mesh::IndexBufferView()const
{
	D3D12_INDEX_BUFFER_VIEW ibv;
	ibv.BufferLocation = m_GPUVertexBuffer->GetGPUVirtualAddress();
	ibv.Format = IndexFormat;
	ibv.SizeInBytes = m_vertexBufferByteSize;

	return ibv;
}



//D3D12_RESOURCE_DESC