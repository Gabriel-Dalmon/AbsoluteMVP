#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init(MeshReferenceDescriptor* desc);

private:
	Mesh* m_pMesh = nullptr;
};

