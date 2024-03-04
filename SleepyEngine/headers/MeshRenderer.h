#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init(Mesh* mesh);

	Mesh* GetMesh();

private:
	Mesh* m_pMesh = nullptr;
};

