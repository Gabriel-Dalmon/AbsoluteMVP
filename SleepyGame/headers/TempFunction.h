#pragma once

class TempFunction : public SleepyEngine
{
public:

	TempFunction(HINSTANCE hInstance);
	~TempFunction() {};

	void BlankInit() override;
	void BlankUpdate() override;
	void BlankPreLoop() override;
};

