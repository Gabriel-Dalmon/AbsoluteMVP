#pragma once
#include"Collider.h"

class ColliderOBB : public Collider
{
public:
	ColliderOBB();
	~ColliderOBB();

	void Init();
	void Orient(XMVECTOR quat);

	BoundingOrientedBox m_box;
};