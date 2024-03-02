#pragma once

#include <map> // Ca marchait sans au campus mais plus maintenant. <map> est supposé être importé dans "pch.h" par Input.cpp
//#include <string>

class Input
{
public:
	Input();
	bool Init();

	void Update();

	bool IsPressed(int key, bool allowHold);
	bool IsHeld(int key);
	bool GotReleased(int key);

	void OnKeyPressed(int key);
	void OnKeyReleased(int key);

private:
	std::map<int, int> InputList;
};