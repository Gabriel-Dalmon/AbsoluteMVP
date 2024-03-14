#pragma once

class PlayerScript : public Script
{
public:
	PlayerScript() {};
	~PlayerScript() {};

	// Init
	// void Init();

	// Choses à faire
	void OnScript() override;
	void Update();


	void Shoot();
	void UpdateHealth(float damage);
	void CriticalDamage();

	float GetHealth() { return m_health; }

	void Die();
	// Release
	void Release();

public:
	GameFactory* m_pGameFactory = nullptr;
	GameState* m_pGameState = nullptr;
	Entity* m_pCamera = nullptr;

	float m_health = 100.0f;
	float m_damage = 10.0f;
	
	float m_criticalChance = 0.05f;

	bool m_isDead = false;

	Transform* m_pTransform = m_pEntity->GetComponent<Transform*>();
};