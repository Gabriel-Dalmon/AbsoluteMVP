#pragma once

class Collider : public Component
{
public:
	Collider();
	~Collider() {};

	// INIT
	void Initialize(ColliderDescriptor* pColliderDescriptor);

private:
};

