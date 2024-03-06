#pragma once

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer() {};

	// INIT
	void Init(Mesh* mesh);

	void Release();

private:
	Mesh* m_pMesh = nullptr;
};

