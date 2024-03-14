#pragma once

class Factory
{
public:
	Factory();
	~Factory();

	void Initialize(ResourceAllocator* rRessourceAllocator);

protected:
	ResourceAllocator* m_pRessourceAllocator = nullptr;
};