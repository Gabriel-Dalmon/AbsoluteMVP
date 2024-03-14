#include "pch.h"

void EnemyScript::OnScript()
{
	Update(); 
	ShootAt(m_pPlayerEntity);
}

void EnemyScript::Update()
{
	m_pEntity->GetComponent<Transform*>()->LookAt(m_pPlayerEntity->GetComponent<Transform*>());
}

void EnemyScript::UpdateHealth(float damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		Die();
	}
}

void EnemyScript::ShootAt(Entity* player)
{
	XMFLOAT3 playerPosition = player->GetComponent<Transform*>()->m_positionVect;
	Entity* bullet = Entity::CreateEmptyEntity();
	Transform* transform = Component::CreateComponent<Transform>();
	bullet->AddComponent<Transform*>(transform); 
}

void EnemyScript::Die()
{

}

void EnemyScript::Release()
{
}

