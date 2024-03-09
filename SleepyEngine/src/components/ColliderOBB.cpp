#include "pch.h"

ColliderOBB::ColliderOBB() {};

ColliderOBB::~ColliderOBB() {};

void ColliderOBB::Init()
{
	MeshRenderer* pMeshRef = m_pEntity->GetComponent<MeshRenderer*>();
	Mesh* pMesh = pMeshRef->GetMesh();
	const int size = pMesh->m_CPUVertexBuffer->size();
	XMFLOAT3* coordinates;
	coordinates = (XMFLOAT3*)malloc(sizeof(XMFLOAT3) * size);
	for (int i = 0; i < size; i++) {
		coordinates[i] = pMesh->m_CPUVertexBuffer->at(i).Pos;
	}
	BoundingOrientedBox::CreateFromPoints(m_box, pMesh->m_indexCount, coordinates, pMesh->m_vertexByteStride);
	(m_box.Orientation.x, m_box.Orientation.y, m_box.Orientation.z, m_box.Orientation.w) = (0.0f, 0.0f, 0.0f, 1.0f);
	free(coordinates);
};

void ColliderOBB::Orient(XMVECTOR quat)
{
	XMStoreFloat4(&m_box.Orientation, quat);
}