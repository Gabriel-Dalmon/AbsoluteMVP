#include "pch.h"
#include "Core/GameState.h"

#include "ECS/Entity.h"
#include "ECS/System.h"

GameState::GameState()
{
}

void GameState::Initialize()
{
}

void GameState::Update(float deltaTime)
{
	for (System* system : m_systemsList)
	{
		system->Update(deltaTime);
	}
	// delete entities
}

void GameState::Enter()
{
}

void GameState::Exit()
{
}

/// <summary>
/// Adds the entity passed in argument into the EntityList, making it handled by the GameState class.
/// </summary>
/// <param name="entity"></param>
void GameState::AddEntity(Entity* entity)
{
	int entityBID = entity->GetComponentsBID();
	for (System* system : m_systemsList)
	{
		if (entityBID & system->GetRequiredComponentsBID())
		{
			system->AddEntity(deltaTime);
		}
	}
	m_entitiesList.push_back(entity);
}


/// <summary>
/// Removes the entity passed in argument from the EntityList, making it not handled by the GameState class.
/// </summary>
/// <param name="entity"></param>
void GameState::RemoveEntity(Entity* entity)
{
	for (int i = 0; i < m_EntityList.size(); i++)
	{
		if (m_EntityList[i] == entity)
		{
			RELEASE(m_EntityList[i]);
			m_EntityList.erase(m_EntityList.begin() + i);
		}
	}
}


/// <summary>
/// Checks if the entity passed in argument is handled by GameState and returns a boolean.
/// </summary>
/// <param name="entity"></param>
/// <returns>True if the entity is currently handled by GameState class. False if it's not.</returns>
bool GameState::CheckEntity(Entity* entity)
{
	for (int i = 0; i < m_EntityList.size(); i++)
	{
		if (m_EntityList[i] == entity)
			return true;
	}
	return false;
}

void GameState::Release()
{
	RELEASE(m_pPreviousGameState);
}


