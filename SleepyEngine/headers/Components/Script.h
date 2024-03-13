#pragma once

class Script : public Component
{
public:
	Script();
	~Script() {};

	// INIT
	void Initialize(ScriptDescriptor* desc);

	// Virtual function
	virtual void OnScript() {};

	void Release();

private:

};
