#include "pch.h"

void PlayGameState::Init()
{
}

void PlayGameState::CreatePlayer()
{
	Entity* player = Entity::CreateEmptyEntity();
	m_pGameFactory->FillPlayer(player);
	AddEntity(player);
}

void PlayGameState::CreateEnemy()
{
	Entity* enemy = Entity::CreateEmptyEntity();
	m_pGameFactory->FillEnemy(enemy);
	AddEntity(enemy);
}

void PlayGameState::CreateScore()
{
	Entity* score = Entity::CreateEmptyEntity();
	// m_pGameFactory->FillScore();
	AddEntity(score);
}


