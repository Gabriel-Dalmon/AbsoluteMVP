#include "pch.h"
#include "System.h"
#include "EventManager.h"

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

void EventManager::HandleEvents()
{
	for (auto& pair : m_InputList)
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

void EventManager::OnKeyPressed(int key)
{
	std::cout << "Key pressed: " << key << std::endl;
}

void EventManager::OnKeyReleased(int key)
{
	std::cout << "Key released: " << key << std::endl;
}
