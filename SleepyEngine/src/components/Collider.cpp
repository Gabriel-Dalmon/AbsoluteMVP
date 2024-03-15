#include "pch.h"

Collider::Collider()
{

}



void Collider::Init(ColliderDescriptor* desc)
{
	m_radius = desc->radius;
}

bool Collider::collideTest(Entity* self, Entity* target)
{
	XMVECTOR selfPos = XMLoadFloat3(&self->GetComponent<Transform*>()->m_positionVect);
	XMVECTOR targetPos = XMLoadFloat3(&target->GetComponent<Transform*>()->m_positionVect);

	XMVECTOR deltaPos = selfPos - targetPos;
	deltaPos *= deltaPos;

	float deltaRadius = self->GetComponent<Collider*>()->m_radius + target->GetComponent<Collider*>()->m_radius;

	if (XMVectorGetX(deltaPos) + XMVectorGetY(deltaPos) + XMVectorGetZ(deltaPos) < deltaRadius * deltaRadius) {
		return true;
	}

	return false;
}