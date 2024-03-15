#include "pch.h"

Collider::Collider()
{
	m_typeFlag = COLLIDER;
}

void Collider::Initialize(ColliderDescriptor* pColliderDescriptor)
{

}

void Collider::Initialize(ColliderDescriptor* desc)
{
	m_radius = desc->radius;
}