#pragma once

class Script : public Component
{
public:
	Script();
	~Script() {};

	// INIT
	void Init() override;

	// Virtual function
	virtual void OnScript();

	void Release();

private:

};

