#pragma once

class Factory 
{
public:
	Factory();
	~Factory();

	// Init
	void Init(RessourceAllocator* rRessourceAllocator);

	// Entity linked functions
	Entity* CreateEmptyEntity();

protected:
	RessourceAllocator* m_pRessourceAllocator;
};