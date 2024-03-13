#pragma once

class ResourceAllocator
{
public:
	ResourceAllocator() {};
	~ResourceAllocator() {};

	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	void Release();

	Mesh* GetMesh(const std::string& fileName);

private:
	std::map<std::string, Mesh*>* m_meshCollection;
	ID3D12Device* m_pDevice;
	ID3D12GraphicsCommandList* m_pCommandList;
};