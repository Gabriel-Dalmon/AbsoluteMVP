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
		// Peut �tre mit dans une m�thode plus sp�cifique type "LookAt()"
		//
		Vector playerPosition = Entity player->GetComponent<Transform*>()
		Entity* bullet = Entity::CreateEmptyEntity();
		Transform* transform = Component::CreateComponent<Transform*>();
		bullet->AddComponent<Transform*>(transform);
		bullet->SetDirection(transform->m_DirVect (norm�));
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

