#pragma once

class Factory 
{
public:
	Factory();
	~Factory();

	// Init
	void Init(RessourceAllocator* rRessourceAllocator);
	void SetSignatureAndPSO(SleepyEngine* pEngine);

protected:
	RessourceAllocator* m_pRessourceAllocator = nullptr;
};