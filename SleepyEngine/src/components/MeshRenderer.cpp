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

Mesh* MeshRenderer::GetMesh() 
{
	return m_pMesh;
};