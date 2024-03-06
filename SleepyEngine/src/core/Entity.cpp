#include "pch.h"
#include "Entity.h"



Entity::Entity()
{
}

void Entity::Init()
{
}

Entity* Entity::CreateEmptyEntity()
{
	Entity* entity = new Entity;
	entity->Init();
	return entity;
}

void Entity::KillSelf()
{
	Clear();
	delete this;
}

void Entity::Clear()
{
	for (int i = 0; i < m_componentsList.size(); i++)
	{
		m_componentsList[i] = nullptr;
		m_componentsList.erase(m_componentsList.begin() + i);
	}
}

