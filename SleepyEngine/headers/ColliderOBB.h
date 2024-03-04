#pragma once
#include"Collider.h"

class ColliderOBB : public Collider
{
public:
	ColliderOBB();
	~ColliderOBB();

	void Init();

	BoundingOrientedBox m_box;
};