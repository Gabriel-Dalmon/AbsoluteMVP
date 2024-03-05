#include "player.h"
#include "Bullet.h"

#include "GameManager.h"

Player::Player() {};

Player::~Player() {};

void Player::Init(GameManager* pGameManager)
{
	m_pGameManager = pGameManager;
}

void Player::Shoot()
{
	Bullet* bullet;
	bullet->Init();
	m_pGameManager->m_entities.push_back(bullet);
}