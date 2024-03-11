#include "pch.h"

void PlayerScript::OnScript()
{
	CriticalDamage();
}

void PlayerScript::Shoot()
{
	Entity* bullet = Entity::CreateEmptyEntity();
	m_pGameFactory->FillBullet(bullet);
	m_pGameState->AddEntity(bullet);

	// TO DO:
	/*
		bullet->SetDirection(x, y, z); Selon la direction de la caméra -> selon l'orientation de la souris
		if (collision avec enemy)
		{
			m_health de enemy -= m_damage de player;
			if (m_health de enemy == 0)
			{
				enemy->Die();
				// Eventuellement changer de game state (pour un boss par exemple)
			}
		}
	*/
}

void PlayerScript::UpdateHealth(float damage)
{
	m_health -= damage;
}

void PlayerScript::CriticalDamage()
{
	srand((unsigned int)time(0));
	int valeur = (rand() % 100) + 1;
	if (valeur == 1 || valeur == 2 || valeur == 3)
	{
		int buffer = m_damage;
		m_damage *= 2;
		Shoot();
		m_damage = buffer;
	}
	Shoot();
}

void PlayerScript::Die()
{
	m_isDead = true;
}

void PlayerScript::Release()
{
	// /!\ ATTENTION A COMMMENT ON APPELLE CE RELEASE (GAMESTATE ET FACTORY POTENTIELLEMENT RELEASE A LA DESTRUCTION DU PLAYER)
	// RELEASE(m_pGameFactory);
	// RELEASE(m_pGameState);
}
