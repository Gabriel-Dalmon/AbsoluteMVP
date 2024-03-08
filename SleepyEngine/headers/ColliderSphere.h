#pragma once

class ColliderSphere : public Collider
{
public:
	ColliderSphere();
	~ColliderSphere();

	void Init(ColliderSphereDescriptor* desc);

	BoundingSphere m_box;

	int CheckCollisionWith(ColliderSphere* target);
};