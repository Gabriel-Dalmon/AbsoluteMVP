#pragma once
#include "Entity.h"

class GameManager;

class Player : public Entity
{
public:
	Player();
	~Player();

	void Init(GameManager* pGameManager);
	void Shoot();

	GameManager* m_pGameManager;
};