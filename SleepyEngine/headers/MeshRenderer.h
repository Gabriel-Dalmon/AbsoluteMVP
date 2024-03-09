#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init(MeshReferenceDescriptor* desc);

	void Release();

	Mesh* GetMesh();

private:
	Mesh* m_pMesh = nullptr;
};

