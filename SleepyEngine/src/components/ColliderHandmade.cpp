#include "pch.h"

bool ColliderHandMade::collideTest(Entity* self, Entity* target)
{
	XMVECTOR selfPos = XMLoadFloat3(&self->GetComponent<Transform*>()->m_positionVect);
	XMVECTOR targetPos = XMLoadFloat3(&target->GetComponent<Transform*>()->m_positionVect);

	XMVECTOR deltaPos = selfPos * selfPos - targetPos * targetPos;

	float deltaRadius = self->GetComponent<ColliderHandMade*>()->m_radius + target->GetComponent<ColliderHandMade*>()->m_radius;

	if (XMVectorGetX(deltaPos) + XMVectorGetY(deltaPos) + XMVectorGetZ(deltaPos) < deltaRadius * deltaRadius) {
		return true;
	}
	
	return false;
}