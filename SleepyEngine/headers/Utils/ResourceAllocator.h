#pragma once

class ResourceAllocator
{
public:
	ResourceAllocator() {};
	~ResourceAllocator() {};

	void Initialize(Device* pDevice, CommandQueue* pCommandQueue);
	void Release();

	Mesh* GetMesh(const std::string& fileName);

    template<typename VertexType>;
    void CreateMesh(std::vector<VertexType>* vertices, std::vector<uint16_t>* indices)
    {
        
        int vertexByteStride = sizeof(VertexType);
        int vertexBufferByteSize = sizeof(VertexType) * vertices->size();
        int indexBufferByteSize = sizeof(uint16_t) * m_indexCount;
        unsigned int indexCount = indices->size();
		ID3D12Resource* pCPUVertexBuffer = nullptr;
		ID3D12Resource* pCPUIndexBuffer = nullptr;
		ID3D12Resource* pGPUVertexBuffer = nullptr;
		ID3D12Resource* pGPUIndexBuffer = nullptr;

        ThrowIfFailed(D3DCreateBlob(vertexBufferByteSize, &CPUVertexBuffer));
        CopyMemory(CPUVertexBuffer->GetBufferPointer(), vertices->data(), vertexBufferByteSize);

        ThrowIfFailed(D3DCreateBlob(indexBufferByteSize, CPUIndexBuffer));
        CopyMemory(CPUIndexBuffer->GetBufferPointer(), indices->data(), indexBufferByteSize);

        m_pCommandAllocator->Reset();
        m_pCommandList->Reset(m_pCommandAllocator, nullptr);

        pGPUVertexBuffer = D3DUtils::CreateDefaultBuffer(m_pDevice->GetD3DDevice(), m_pCommandList, vertices->data(), vertexBufferByteSize, pUploaderVertexBuffer);
        pGPUIndexBuffer = D3DUtils::CreateDefaultBuffer(m_pDevice->GetD3DDevice(), m_pCommandList, indices->data(), indexBufferByteSize, pUploaderIndexBuffer);

        m_pCommandList->Close();
        ID3D12CommandList* commandLists[] = { m_pCommandList };
        m_pCommandQueue->Execute(_countof(commandLists), commandLists);
        m_pCommandQueue->Flush();

        Mesh* pMesh = new Mesh();
        pMesh->Initialize(vertexByteStride, vertexBufferByteSize, indexCount, indexBufferByteSize, pCPUVertexBuffer, pCPUIndexBuffer, pGPUVertexBuffer, pGPUIndexBuffer);

    };

	Mesh* CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount);

private:
	std::map<std::string, Mesh*>* m_meshCollection;
	Device* m_pDevice;

	CommandQueue* m_pCommandQueue;
	ID3D12GraphicsCommandList* m_pCommandList;
	ID3D12CommandAllocator* m_pCommandAllocator;
};