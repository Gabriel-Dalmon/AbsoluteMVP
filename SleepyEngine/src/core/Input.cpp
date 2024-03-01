#include "pch.h"
#include "Input.h"
//#include <vector>
//#include <iostream>
//#include <Windows.h>

template<typename Key, typename Value>
std::ostream& operator << (std::ostream& os, std::map<Key, Value>& map)
{
	os << "{\n";
	for (const auto& pair : map)
	{
		os << "\t{" << pair.first << " => " << pair.second << "}\n";
	}
	os << "}";

	return os;
}

Input::Input()
{}

bool Input::Init()
{
	std::vector<int> GodDamnLongInputIdList = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'M', 'N', 'L', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		// Left, right and middle buttons. Have a gamer mouse with 14 buttons? Too bad!
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,
		VK_RETURN, VK_SPACE, VK_DELETE,
		VK_CONTROL, VK_SHIFT, VK_MENU, VK_TAB, VK_ESCAPE
	};

	for (int i = 0; i < GodDamnLongInputIdList.size(); i++)
	{
		InputList.insert({ GodDamnLongInputIdList[i], 0 });
	}
	std::cout << InputList << std::endl;
	return true;
}

void Input::Update()
{
	for (auto& pair : InputList)
	{
		SHORT keyState = GetAsyncKeyState(pair.first);
		if (keyState & 0x8000 && pair.second >= 1)
			pair.second = 2;
		else if (keyState & 0x1 && pair.second == 0)
			pair.second = 1;
		else if (pair.second > 0)
			pair.second = -1;
		else
			pair.second = 0;

		if (pair.second > 0)
			OnKeyPressed(pair.first);
		else if (pair.second == -1)
			OnKeyReleased(pair.first);
	}
}

//#include <map>
std::pair<int, int> getKeyPair(int key, std::map<int, int> InputList)
{
	for (const auto& pair : InputList)
	{
		if (pair.first == key) {
			return pair;
		}
	}
}

bool Input::IsPressed(int key, bool allow_hold)
{
	std::pair<int, int> pair = getKeyPair(key, InputList);
	if (allow_hold)
		return pair.second > 0;
	return pair.second == 1;
}

bool Input::IsHeld(int key)
{
	std::pair<int, int> pair = getKeyPair(key, InputList);
	return pair.second == 2;
}

bool Input::GotReleased(int key)
{
	std::pair<int, int> pair = getKeyPair(key, InputList);
	return pair.second == -1;
}

void Input::OnKeyPressed(int key)
{
	std::cout << "Key pressed: " << key << std::endl;
}

void Input::OnKeyReleased(int key)
{
	std::cout << "Key released: " << key << std::endl;
}