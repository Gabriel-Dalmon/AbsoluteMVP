#include "pch.h"

MeshRenderer::MeshRenderer()
{
}

void MeshRenderer::Init(Mesh* mesh)
{
	m_pMesh = mesh;
}

void MeshRenderer::Release()
{
	RELEASE(m_pMesh);
}
