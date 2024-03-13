#include "pch.h"

bool ColliderHandMade::collideTest(Entity* self, Entity* target)
{
	XMVECTOR selfPos = XMLoadFloat3(&self->GetComponent<Transform*>()->m_positionVect);
	XMVECTOR targetPos = XMLoadFloat3(&target->GetComponent<Transform*>()->m_positionVect);

	float deltaX = XMVectorGetX(selfPos) * XMVectorGetX(selfPos) - XMVectorGetX(targetPos) * XMVectorGetX(targetPos);
	float deltaY = XMVectorGetY(selfPos) * XMVectorGetY(selfPos) - XMVectorGetY(targetPos) * XMVectorGetY(targetPos);
	float deltaZ = XMVectorGetZ(selfPos) * XMVectorGetZ(selfPos) - XMVectorGetZ(targetPos) * XMVectorGetZ(targetPos);

	float deltaRadius = self->GetComponent<ColliderHandMade*>()->m_radius + target->GetComponent<ColliderHandMade*>()->m_radius;

	if (deltaX < deltaRadius && deltaY < deltaRadius && deltaZ < deltaRadius) {
		return true;
	}
	
	return false;
}