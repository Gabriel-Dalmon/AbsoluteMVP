#pragma once

class Factory 
{
public:
	Factory();
	~Factory();

	// Init
	void Init(RessourceAllocator* rRessourceAllocator);

protected:
	RessourceAllocator* m_pRessourceAllocator = nullptr;
};