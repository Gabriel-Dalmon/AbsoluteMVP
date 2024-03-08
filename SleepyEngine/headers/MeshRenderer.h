#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init(MeshReferenceDescriptor* desc);

	void Release();

private:
	Mesh* m_pMesh = nullptr;
};

