#pragma once

class EnemyScript : public Script
{
public:
	EnemyScript() {};
	~EnemyScript() {};

	// Init
	// Initialize();

	// OnScript()
	void OnScript() override;

	void UpdateHealth(float damage);
	void ShootAt();

	void Die();

	// Release
	void Release();

private:
	float m_health = 100.0f;
	float m_damage = 10.0f;
};
