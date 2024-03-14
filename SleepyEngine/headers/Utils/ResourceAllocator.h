#pragma once

class ResourceAllocator
{
public:
	ResourceAllocator() {};
	~ResourceAllocator() {};

	void Initialize(Device* pDevice, ID3D12CommandQueue* pCommandQueue);
	void Release();

	Mesh* GetMesh(const std::string& fileName);

	Mesh* CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount);

private:
	std::map<std::string, Mesh*>* m_meshCollection;
	Device* m_pDevice;
	ID3D12CommandQueue* m_pCommandQueue;
};