#pragma once

class Collider : public Component
{
public:
	Collider();
	~Collider() {};

	// INIT
	void Initialize() override;

public:
	float GetRadius() { return m_radius; };

private:
	float m_radius;
};

