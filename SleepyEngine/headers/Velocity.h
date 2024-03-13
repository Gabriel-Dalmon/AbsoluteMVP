#pragma once

class Velocity : public Component
{
public:
	Velocity();
	~Velocity();

	void Init(VelocityDescriptor*);

public:
	void SetVelocity(float x, float y, float z);
	XMVECTOR GetVelocity();

private:
	float m_x = 0;
	float m_y = 0;
	float m_z = 0;
};