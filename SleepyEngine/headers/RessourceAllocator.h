#pragma once

class RessourceAllocator 
{
public:
	RessourceAllocator() {};
	~RessourceAllocator() {};

	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	void Release();

	Mesh* getMesh(const std::string& fileName);

	Mesh* CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount);

private:
	std::map<std::string, Mesh*>* m_meshCollection;
	ID3D12Device* m_pDevice;
	ID3D12GraphicsCommandList* m_pCommandList;
};