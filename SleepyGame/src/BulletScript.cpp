#include "pch.h"

void BulletScript::OnScript()
{
	Velocity* velocity = m_pEntity->GetComponent<Velocity*>();
	Transform* transform = m_pEntity->GetComponent<Transform*>();
	float x = transform->m_positionVect.x + XMVectorGetX(velocity->GetVelocity());
	float y = transform->m_positionVect.y + XMVectorGetY(velocity->GetVelocity());
	float z = transform->m_positionVect.z + XMVectorGetZ(velocity->GetVelocity());
	std::cerr << "x : " << x << std::endl;
	std::cerr << "y : " << y << std::endl;
	std::cerr << "z : " << z << std::endl;

	transform->SetPosition(x, y, z);


	/*for (int i = 0; i < m_entities.size(); i++) {
		for (int j = m_entities.size(); j >= i; i--) {
			ColliderHandMade::collideTest(m_entities[i], m_entities[j]);
		}
	}*/
}