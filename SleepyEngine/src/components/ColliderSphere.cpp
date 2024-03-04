#include "pch.h"
#include "ColliderSPHERE.h"
#include "entity.h";
#include "MeshRenderer.h"
#include "Mesh.h"

ColliderSphere::ColliderSphere() {};

ColliderSphere::~ColliderSphere() {};

void ColliderSphere::Init()
{
	MeshRenderer* pMeshRef = m_pEntity->GetComponent<MeshRenderer*>();
	Mesh* pMesh = pMeshRef->GetMesh();
	const int size = pMesh->m_CPUVertexBuffer->size();
	XMFLOAT3* coordinates;
	coordinates = (XMFLOAT3*)malloc(sizeof(XMFLOAT3) * size);
	for (int i = 0; i < size; i++) {
		coordinates[i] = pMesh->m_CPUVertexBuffer->at(i).Pos;
	}
	BoundingSphere::CreateFromPoints(m_box, pMesh->m_indexCount, coordinates, pMesh->m_vertexByteStride);
	free(coordinates);
}