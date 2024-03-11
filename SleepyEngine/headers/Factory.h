#pragma once

class Factory 
{
public:
	Factory();
	~Factory();
	void Init(RessourceAllocator* rRessourceAllocator);

protected:
	RessourceAllocator* m_pRessourceAllocator;
};