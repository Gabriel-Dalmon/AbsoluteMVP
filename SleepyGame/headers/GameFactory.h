#pragma once

class GameFactory : public Factory
{
public:
	GameFactory() {};
	~GameFactory() {};

	// Init
	void Initialize();

	// Entity linked functions
	Entity* CreateEmptyEntity();

	void FillPlayer(Entity* pEntity);
	void FillEnemy(Entity* pEntity);
	void FillBullet(Entity* pEntity);
	void FillSkybox(Entity* pEntity);
	void FillSphere(Entity* pEntity);

	// Release
	void Release();

private:
};