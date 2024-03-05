#include "pch.h"
#include "Mesh.h"

#include "MeshRenderer.h"

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
