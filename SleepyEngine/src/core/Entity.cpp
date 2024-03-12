#include "pch.h"

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

Entity* Entity::GetParent()
{
	if (m_pParentEntity == nullptr)
		return nullptr;

	return m_pParentEntity;
}

void Entity::SetParent(Entity* parent)
{
	if (m_pParentEntity == nullptr)
	{
		m_pParentEntity = parent;
		parent->AddChild(this);
		return;
	}

	m_pParentEntity->RemoveChild(this);
	m_pParentEntity = parent;
}

void Entity::RemoveParent()
{
	if (m_pParentEntity != nullptr)
		m_pParentEntity = nullptr;
	else
		std::cout << "This entity has no parent." << std::endl;
}

void Entity::AddChild(Entity* child)
{
	for (int i = 0; i < m_ChildrenEntities.size(); i++)
		if (m_ChildrenEntities[i] == child)
			std::cout << "The child you're trying to pass in the children of this entity already exists." << std::endl;
	return;

	m_ChildrenEntities.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	for (int i = 0; i < m_ChildrenEntities.size(); i++)
	{
		if (m_ChildrenEntities[i] == child)
		{
			m_ChildrenEntities.erase(m_ChildrenEntities.begin() + i);
		}
		else
			std::cout << "The entity you passed in argument is not a child of this Entity." << std::endl;
	}
}

std::vector<Entity*> Entity::GetChildren()
{
	return m_ChildrenEntities;
}

void Entity::Release()
{
	for (int i = 0; i < m_componentsList.size(); i++)
	{
		m_componentsList[i] = nullptr;
		m_componentsList.erase(m_componentsList.begin() + i);
		std::cout << "All the component were cleared from this Entity." << std::endl;

		m_ChildrenEntities[i] = nullptr;
		m_ChildrenEntities.erase(m_ChildrenEntities.begin() + i);
		std::cout << "All the children were removed from this Entity." << std::endl;
		
		m_pParentEntity = nullptr;
	}
	delete this;
}

