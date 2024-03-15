#pragma once

class Collider : public Component
{
public:
	Collider();
	~Collider() {};

	// INIT
	void Init(ColliderDescriptor*);

	float m_radius;

	static bool collideTest(Entity* self, Entity* target);

private:
};

