#pragma once
#include"Collider.h"

class ColliderSphere : public Collider
{
public:
	ColliderSphere();
	~ColliderSphere();

	void Init();

	// BoundingSphere m_box;
};