#include "ColliderOBB.h"
#include "entity.h";
#include "MeshRenderer.h"

ColliderOBB::ColliderOBB() {};

ColliderOBB::~ColliderOBB() {};

void ColliderOBB::Init()
{
	MeshRenderer* mesh = m_pEntity->GetComponent<MeshRenderer*>();
	BoundingOrientedBox::CreateFromPoints(m_box, mesh->p_pMesh);
};