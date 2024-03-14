#include "pch.h"
#include "D3DUtils.h"

Mesh::Mesh() {}

Mesh::~Mesh() {}


void Mesh::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<uint16_t>* indices)
{
	m_pName = "sphereGeo";
	m_vertexByteStride = sizeof(VertexTexture);
	m_vertexBufferByteSize = sizeof(VertexTexture) * vertices->size();
	m_indexCount = indices->size();
	m_indexBufferByteSize = sizeof(uint16_t) * m_indexCount;
	std::cout << "Index BSize" << m_indexBufferByteSize << std::endl;

	ThrowIfFailed(D3DCreateBlob(m_vertexBufferByteSize, &m_CPUVertexBuffer));
	CopyMemory(m_CPUVertexBuffer->GetBufferPointer(), vertices->data(), m_vertexBufferByteSize);

	ThrowIfFailed(D3DCreateBlob(m_indexBufferByteSize, &m_CPUIndexBuffer));
	CopyMemory(m_CPUIndexBuffer->GetBufferPointer(), indices->data(), m_indexBufferByteSize);

	m_pGPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices->data(), m_vertexBufferByteSize, m_pUploaderVertexBuffer);
	m_pGPUIndexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, indices->data(), m_indexBufferByteSize, m_pUploaderIndexBuffer);

	Submesh submesh;
	submesh.IndexCount = (UINT)indices->size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	m_drawArgs["sphere"] = submesh;
}

void Mesh::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<VertexTexture>* vertices, std::vector<uint16_t>* indices)
{
	m_pName = "boxGeo";
	m_vertexByteStride = sizeof(VertexTexture);
	m_vertexBufferByteSize = sizeof(VertexTexture) * vertices->size();
	m_indexCount = indices->size();
	m_indexBufferByteSize = sizeof(uint16_t) * m_indexCount;
	std::cout << "Index BSize" << m_indexBufferByteSize << std::endl;

	ThrowIfFailed(D3DCreateBlob(m_vertexBufferByteSize, &m_CPUVertexBuffer));
	CopyMemory(m_CPUVertexBuffer->GetBufferPointer(), vertices->data(), m_vertexBufferByteSize);

	ThrowIfFailed(D3DCreateBlob(m_indexBufferByteSize, &m_CPUIndexBuffer));
	CopyMemory(m_CPUIndexBuffer->GetBufferPointer(), indices->data(), m_indexBufferByteSize);

	m_pGPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices->data(), m_vertexBufferByteSize, m_pUploaderVertexBuffer);
	m_pGPUIndexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, indices->data(), m_indexBufferByteSize, m_pUploaderIndexBuffer);

	Submesh submesh;
	submesh.IndexCount = (UINT)indices->size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	m_drawArgs["box"] = submesh;
}

void Mesh::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<VertexColor>* vertices, std::vector<uint16_t>* indices)
{
	m_pName = "boxGeo";
	m_vertexByteStride = sizeof(VertexColor);
	m_vertexBufferByteSize = sizeof(VertexColor) * vertices->size();
	m_indexCount = indices->size();
	m_indexBufferByteSize = sizeof(uint16_t) * m_indexCount;
	std::cout << "Index BSize" << m_indexBufferByteSize << std::endl;

	ThrowIfFailed(D3DCreateBlob(m_vertexBufferByteSize, &m_CPUVertexBuffer));
	CopyMemory(m_CPUVertexBuffer->GetBufferPointer(), vertices->data(), m_vertexBufferByteSize);

	ThrowIfFailed(D3DCreateBlob(m_indexBufferByteSize, &m_CPUIndexBuffer));
	CopyMemory(m_CPUIndexBuffer->GetBufferPointer(), indices->data(), m_indexBufferByteSize);

	m_pGPUVertexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, vertices->data(), m_vertexBufferByteSize, m_pUploaderVertexBuffer);
	m_pGPUIndexBuffer = D3DUtils::CreateDefaultBuffer(device, commandList, indices->data(), m_indexBufferByteSize, m_pUploaderIndexBuffer);

	Submesh submesh;
	submesh.IndexCount = (UINT)indices->size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	m_drawArgs["box"] = submesh;
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