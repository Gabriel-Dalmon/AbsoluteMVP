#include "pch.h"
#include <typeinfo>


Factory::Factory() {};

Factory::~Factory() {};

void Factory::Init(RessourceAllocator* pRessourceAllocator)
{
	m_pRessourceAllocator = pRessourceAllocator;
}
