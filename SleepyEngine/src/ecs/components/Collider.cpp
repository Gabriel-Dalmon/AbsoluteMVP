#include "pch.h"

Collider::Collider()
{
	m_typeFlag = COLLIDER;
}

void Collider::Initialize(ColliderDescriptor* pColliderDescriptor)
{
	m_radius = pColliderDescriptor->radius;
}