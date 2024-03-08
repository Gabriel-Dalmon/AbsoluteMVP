#include "pch.h"
#include "Mesh.h"

#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}

void MeshRenderer::Init(MeshReferenceDescriptor* desc)
{
	m_pMesh = desc->meshRef;
}
