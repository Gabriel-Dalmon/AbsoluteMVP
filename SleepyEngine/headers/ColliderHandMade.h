#pragma once


class ColliderHandMade : public Component
{
public:
	float m_radius;

	static bool collideTest(Entity* self, Entity* target);
};