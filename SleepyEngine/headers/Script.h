#pragma once
#include "Component.h"

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

