#pragma once

struct Submesh
{
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	INT BaseVertexLocation = 0;

	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;

	std::vector<uint16_t>& GetIndices16()
	{
		if (mIndices16.empty())
		{
			mIndices16.resize(Indices.size());
			for (size_t i = 0; i < Indices.size(); ++i)
				mIndices16[i] = static_cast<uint16_t>(Indices[i]);
		}

		return mIndices16;
	}
private:
	std::vector<uint16_t> mIndices16;
	// Physic stuff below, letting it in comment to treat it later
	// DirectX::BoundingBox Bounds;
};


class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

	// Init
	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<Vertex>* vertices, std::vector<uint16_t>* indices);
	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<VertexTexture>* vertices, std::vector<uint16_t>* indices);
	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, std::vector<VertexColor>* vertices, std::vector<uint16_t>* indices);

	// Release
	void Release();

	char* m_pName;

	ID3DBlob* m_CPUVertexBuffer;
	ID3DBlob* m_CPUIndexBuffer;

	Microsoft::WRL::ComPtr<ID3D12Resource> m_pGPUVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pGPUIndexBuffer = nullptr;

	ID3D12Resource* m_pUploaderVertexBuffer = nullptr;
	ID3D12Resource* m_pUploaderIndexBuffer = nullptr;


	int m_vertexByteStride = 0;
	int m_vertexBufferByteSize = 0;
	DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
	int m_indexBufferByteSize = 0;
	unsigned int m_indexCount;

	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;

	std::unordered_map<std::string, Submesh> m_drawArgs;
};