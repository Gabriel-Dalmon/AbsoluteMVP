#include "pch.h"

void GameSystem::Initialize()
{

}

void GameSystem::UNSAFE_AddEntity(Entity* entity)
{
	GameEntityData* pEntityData = new GameEntityData();
	pEntityData->pEntity = entity;
	pEntityData->pScript = entity->GetComponent<Script>();
	m_entitiesDataList.push_back(pEntityData);
}

void GameSystem::UNSAFE_RemoveEntity(Entity* entity)
{
	for (int i = 0; i < m_entitiesDataList.size(); i++)
	{
		if (m_entitiesDataList[i]->pEntity == entity)
		{
			delete m_entitiesDataList[i];
			m_entitiesDataList.erase(m_entitiesDataList.begin() + i);
		}
	}
}

void GameSystem::Update(float deltaTime)
{
	for (GameEntityData* entity : m_entitiesDataList)
	{
		entity->pScript->OnScript();
	}
}