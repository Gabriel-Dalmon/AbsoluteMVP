#include "pch.h"

void EnemyScript::OnScript()
{
}

void EnemyScript::UpdateHealth(float damage)
{
	m_health -= damage;
}

void EnemyScript::ShootAt()
{
	// TO DO:
	/*
		// Peut être mit dans une méthode plus spécifique type "LookAt()"
		//
		Vector playerPosition = Entity player->GetComponent<Transform*>()
		Entity* bullet = Entity::CreateEmptyEntity();
		Transform* transform = Component::CreateComponent<Transform*>();
		bullet->AddComponent<Transform*>(transform);
		bullet->SetDirection(transform->m_DirVect (normé));
		//

		if (collision avec le player)
		{
			UpdateHealth(m_damage de enemy);
			if (m_health de player <= 0)
			{
				player->Die();
				// Eventuellement changer de GameState
			}
		}
	*/
}

void EnemyScript::Die()
{

}

