#pragma once

class Script : public Component
{
public:
	Script();

	// INIT
	void Init() override;

	// Virtual function
	virtual void OnScript() {};

	void Release();

	Entity m_pEntity;

private:

};

