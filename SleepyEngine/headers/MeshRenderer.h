#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init(Mesh* mesh);

private:
	Mesh* m_pMesh = nullptr;
};

