#pragma once

class GameFactory : public Factory
{
public:
	GameFactory() {};
	~GameFactory() {};

	// Init
	void Init();

	// Entity linked functions
	Entity* CreateEmptyEntity();

	void FillPlayer(Entity* pEntity);
	void FillEnemy(Entity* pEntity);
	void FillBullet(Entity* pEntity);

	// Release
	void Release();

private:
};