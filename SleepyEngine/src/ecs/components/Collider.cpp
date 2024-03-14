#include "pch.h"

Collider::Collider()
{

}

void Collider::Initialize(ColliderDescriptor* desc)
{
	m_radius = desc->radius;
}