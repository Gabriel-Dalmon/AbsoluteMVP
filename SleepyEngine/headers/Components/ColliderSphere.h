#pragma once

class ColliderSphere : public Collider
{
public:
	ColliderSphere();
	~ColliderSphere();

	void Initialize(ColliderSphereDescriptor* pColliderSphere) {};

	// BoundingSphere m_box;
};