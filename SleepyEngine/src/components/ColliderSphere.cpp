#include "pch.h"

ColliderSphere::ColliderSphere() {};

ColliderSphere::~ColliderSphere() {};

void ColliderSphere::Init(ColliderSphereDescriptor* desc)
{
	m_box.Center = desc->center;
	m_box.Radius = desc->radius;
}

int ColliderSphere::CheckCollisionWith(ColliderSphere* target)
{
	if (m_box.Contains(target->m_box) != DISJOINT) {
		return true;
	}
	return false;
}

/*
DISJOINT = 0,
INTERSECTS = 1,
CONTAINS = 2
*/