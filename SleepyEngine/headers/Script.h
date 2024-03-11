#pragma once
#include "ECS/Component.h"

class Script : public Component
{
public:
	Script();
	~Script() {};

	// INIT
	void Initialize() override;

	void Release();

private:

};

