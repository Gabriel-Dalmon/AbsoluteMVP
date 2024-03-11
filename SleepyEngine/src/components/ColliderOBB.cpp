#include "pch.h"

ColliderOBB::ColliderOBB() {};

ColliderOBB::~ColliderOBB() {};

void ColliderOBB::Init()
{
	MeshRenderer* mesh = m_pEntity->GetComponent<MeshRenderer>();
};