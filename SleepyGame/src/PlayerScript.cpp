#include "pch.h"

void PlayerScript::OnScript()
{
	Update();
}

void PlayerScript::Update()
{
}

void PlayerScript::Shoot()
{
	Entity* bullet = Entity::CreateEmptyEntity();
	m_pGameFactory->FillBullet(bullet);
	m_pGameState->AddEntity(bullet); 

	Transform* CamTrans = m_pCamera->GetComponent<Transform*>();

	bullet->GetComponent<Transform*>()->SetRotation(CamTrans);
}

void PlayerScript::UpdateHealth(float damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		Die();
	}
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
		return;
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
