#pragma once

#include <DirectXMath.h>
#include <d3d12.h>
#include <unordered_map>

#include "Components.h"


using namespace DirectX;

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


class Mesh : Components
{
public:
	Mesh();
	~Mesh();

	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<int>* indices);

	char* name;

	//yet clueless about parting following stuff in  gpu / cpu / uploader

	std::vector<Vertex>* m_CPUVertexBuffer;
	std::vector<int>* m_CPUIndexBuffer;
	
	ID3D12Resource* m_GPUVertexBuffer;
	ID3D12Resource* m_GPUIndexBuffer;
	
	ID3D12Resource* m_uploaderVertexBuffer;
	ID3D12Resource* m_uploaderIndexBuffer;


	int m_vertexByteStride = 0;
	int m_vertexBufferByteSize = 0;
	DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT; // clueless about it but seems usefull somewhere
	int m_indexBufferByteSize = 0;

	// Physic stuff below, letting it in comment to treat it later
	//DirectX::BoundingBox Bounds;
};