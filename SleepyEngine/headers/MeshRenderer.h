#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init();

private:
	Mesh* m_pMesh = nullptr;
};

