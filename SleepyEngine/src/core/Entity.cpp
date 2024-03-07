#include "pch.h"
#include "ECS/Entity.h"

Entity::Entity()
{
}

void Entity::Init()
{
}

void Entity::Release()
{
	for (int i = 0; i < m_componentsList.size(); i++)
	{
		m_componentsList[i] = nullptr;
		m_componentsList.erase(m_componentsList.begin() + i);
	}
}

