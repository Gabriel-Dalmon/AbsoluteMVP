#pragma once
#include <vector>

class Entity;

class GameState
{
public:
	GameState();
	~GameState() {};

	// INIT
	// void Init();

	// SETTER / GETTER
	// GameState* CurrentGameState();

	// Update
	
private:
	std::vector<Entity*> m_EntityList;
	std::vector<int> m_SystemList;


};

