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



class Velocity : public Component
{
public:
	Velocity() {};
	~Velocity() {};

	void Init();

public:
	void SetVelocity(float x, float y, float z);
	XMVECTOR GetVelocity();

private:
	float m_x = 0;
	float m_y = 0;
	float m_z = 0;
};