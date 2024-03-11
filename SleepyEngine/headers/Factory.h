#pragma once

class Factory 
{
public:
	Factory();
	~Factory();
	void Init(RessourceAllocator* rRessourceAllocator);

	void FillPlayer(Entity* pEntity);

protected:
	RessourceAllocator* m_pRessourceAllocator;
};