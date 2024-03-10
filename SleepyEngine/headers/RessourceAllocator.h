#pragma once

#include <unordered_map>
#include <string>

class Mesh;

class RessourceAllocator 
{
public:
	RessourceAllocator() {};
	~RessourceAllocator() {};

	void Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	Mesh* getMesh(const std::string& fileName);

private:
	std::unordered_map<std::string, Mesh*> m_meshCollection;
	ID3D12Device* m_pDevice;
	ID3D12GraphicsCommandList* m_pCommandList;
};