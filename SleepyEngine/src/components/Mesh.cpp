#include <vector>

#include "Mesh.h"
#include "D3DUtils.h"

Mesh::Mesh() {}

Mesh::~Mesh() {}

void Mesh::Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<int>* indices)
{
	m_GPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices, sizeof(Vertex), *m_uploaderVertexBuffer);
	m_GPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices, sizeof(Vertex), *m_uploaderIndexBuffer);

	m_vertexByteStride = sizeof(Vertex);
	m_vertexBufferByteSize = sizeof(Vertex) * vertices->size();
	m_indexBufferByteSize = sizeof(Vertex) * indices->size();
}

//D3D12_RESOURCE_DESC