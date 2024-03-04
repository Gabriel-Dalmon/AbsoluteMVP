#include "pch.h"
#include "GameState.h"

#include "Entity.h"

GameState::GameState()
{
}

void GameState::Init()
{
}

void GameState::Update()
{
	for (int i = 0; i < m_SystemList.size(); i++)
	{
		// m_SystemList[i].Update();
	}
}

void GameState::Enter()
{
}

void GameState::Exit()
{
}

void GameState::AddEntity(Entity* entity)
{
	m_EntityList.push_back(entity); 
}

void GameState::RemoveEntity(Entity* entity)
{
	for (int i = 0; i < m_EntityList.size(); i++)
	{
		if (m_EntityList[i] = entity)
		{
			entity->Clear();
			m_EntityList.erase(m_EntityList.begin() + i);
		}
	}
}


