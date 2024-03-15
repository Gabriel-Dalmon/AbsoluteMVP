#include "pch.h"

MeshReference::MeshReference()
{
	m_typeFlag = MESH_REFERENCE;
}

void MeshReference::Initialize(MeshReferenceDescriptor* desc)
{
	m_pMesh = desc->pMeshReference;
}

void MeshReference::Release()
{
}
