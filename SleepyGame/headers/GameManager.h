#pragma once
#include "Enemy.h"
#include "Player.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	void Setup();
	Enemy* SpawnEnnemy();

	std::vector<Entity*> m_entities;
};