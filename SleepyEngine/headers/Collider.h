#pragma once
#include "ECS/Component.h"

class Collider : public Component
{
public:
	Collider();
	~Collider() {};

	// INIT
	void Init() override;

private:
};

