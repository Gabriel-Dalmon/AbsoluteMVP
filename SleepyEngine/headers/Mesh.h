#pragma once

#include "Component.h"

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

	// Init
	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<int>* indices);

	// Release
	void Release();

	char* m_pName;

	std::vector<Vertex>* m_CPUVertexBuffer;
	std::vector<int>* m_CPUIndexBuffer;
	
	ID3D12Resource* m_pGPUVertexBuffer = nullptr;
	ID3D12Resource* m_pGPUIndexBuffer = nullptr;
	
	ID3D12Resource* m_pUploaderVertexBuffer = nullptr;
	ID3D12Resource* m_pUploaderIndexBuffer = nullptr;


	int m_vertexByteStride = 0;
	int m_vertexBufferByteSize = 0;
	DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
	int m_indexBufferByteSize = 0;
	int m_indexCount;

	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;
	

	// Physic stuff below, letting it in comment to treat it later
	// DirectX::BoundingBox Bounds;
};