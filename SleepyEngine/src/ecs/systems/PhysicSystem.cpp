#include "pch.h"


void PhysicSystem::Initialize()
{
	m_requiredComponentsFlags = TRANSFORM | COLLIDER;
}

void PhysicSystem::UNSAFE_AddEntity(Entity* entity)
{
	PhysicEntityData* pEntityData = new PhysicEntityData();
	pEntityData->pEntity = entity;
	pEntityData->pTransform = entity->GetComponent<Transform>();
	pEntityData->pCollider = entity->GetComponent<Collider>();
	m_entitiesDataList.push_back(pEntityData);
}

void PhysicSystem::UNSAFE_RemoveEntity(Entity* entity)
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

void PhysicSystem::Update(float deltaTime)
{
	for (int i = 0; i < m_entitiesDataList.size(); i++)
	{
		for (int j = m_entitiesDataList.size() - 1; j > i; j--)
		{
			if (CheckCollision(m_entitiesDataList[i], m_entitiesDataList[j]))
			{
				// Callback here
			}
		}
	}
}

bool PhysicSystem::CheckCollision(PhysicEntityData* self, PhysicEntityData* target)
{
	XMVECTOR selfPos = XMLoadFloat3(&self->pTransform->m_positionVect);
	XMVECTOR targetPos = XMLoadFloat3(&target->pTransform->m_positionVect);

	XMVECTOR deltaPos = selfPos - targetPos;
	deltaPos *= deltaPos;

	float deltaRadius = self->pCollider->GetRadius() + target->pCollider->GetRadius();

	if (XMVectorGetX(deltaPos) + XMVectorGetY(deltaPos) + XMVectorGetZ(deltaPos) < deltaRadius * deltaRadius) {
		return true;
	}

	return false;
}