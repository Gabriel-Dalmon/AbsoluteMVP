#include "pch.h"

MeshRenderer::MeshRenderer()
{
}

void MeshRenderer::Init(MeshReferenceDescriptor* desc)
{
	m_pMesh = desc->meshRef;
}

void MeshRenderer::Release()
{
	RELEASE(m_pMesh);
}
