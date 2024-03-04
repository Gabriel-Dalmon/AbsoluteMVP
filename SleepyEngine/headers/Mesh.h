#pragma once

#include <DirectXMath.h>
#include <d3d12.h>
#include <unordered_map>

#include "Component.h"
#include "Transform.h"

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


class Mesh : Component
{
public:
	Mesh();
	~Mesh();

	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<int>* indices);

	char* name;

	std::vector<Vertex>* m_CPUVertexBuffer;
	std::vector<int>* m_CPUIndexBuffer;
	
	ID3D12Resource* m_GPUVertexBuffer;
	ID3D12Resource* m_GPUIndexBuffer;
	
	ID3D12Resource* m_uploaderVertexBuffer;
	ID3D12Resource* m_uploaderIndexBuffer;


	int m_vertexByteStride = 0;
	int m_vertexBufferByteSize = 0;
	DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
	int m_indexBufferByteSize = 0;
	int m_indexCount;

	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;

	Transform transform;
	

	// Physic stuff below, letting it in comment to treat it later
	//DirectX::BoundingBox Bounds;
};