#pragma once

class Factory 
{
public:
	Factory();
	~Factory();
	void Init(RessourceAllocator* rRessourceAllocator);

private:
	RessourceAllocator* m_pRessourceAllocator;

public:
	void FillPlayer(Entity* pEntity);
	void FillEnemy(Entity* pEntity);
	void FillBullet(Entity* pEntity);
};