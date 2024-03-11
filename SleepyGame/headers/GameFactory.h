#pragma once

class GameFactory : public Factory
{
public:
	void FillPlayer(Entity* pEntity);
	void FillEnemy(Entity* pEntity);
	void FillBullet(Entity* pEntity);
};