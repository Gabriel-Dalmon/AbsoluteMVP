#pragma once

class Factory 
{
public:
	Factory();
	~Factory();

	// Init
	void Init(RessourceAllocator* rRessourceAllocator);

	void FillPlayer(Entity* pEntity);
	void FillEnemy(Entity* pEntity);
	void FillBullet(Entity* pEntity);

protected:
	RessourceAllocator* m_pRessourceAllocator = nullptr;
};