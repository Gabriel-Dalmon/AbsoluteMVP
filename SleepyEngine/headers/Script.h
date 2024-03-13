#pragma once

class Script : public Component
{
public:
	Script();
	~Script() {};

	// INIT
	void Init(ScriptDescriptor* desc);

	// Virtual function
	virtual void OnScript() {};

	void Release();

private:

};

