#pragma once

class MeshReference : public Component
{
public:
	MeshReference();
	~MeshReference() {};

	// INIT
	void Initialize(MeshReferenceDescriptor* desc) override;

	// SETTER / GETTER
	Mesh* GetMesh() { return m_pMesh; }

	// Release
	void Release();

private:
	Mesh* m_pMesh = nullptr;
};

