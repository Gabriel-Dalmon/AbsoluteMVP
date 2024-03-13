#include "pch.h"

ColliderOBB::ColliderOBB() {};

ColliderOBB::~ColliderOBB() {};

void ColliderOBB::Init()
{
	MeshReference* mesh = m_pEntity->GetComponent<MeshReference>();
};