#pragma once
#include "ECS/Component.h"

class Script : public Component
{
public:
	Script();
	~Script() {};

	// INIT
	void Init() override;

	void Release();

private:

};

