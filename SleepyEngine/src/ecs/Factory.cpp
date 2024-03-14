#include "pch.h"

Factory::Factory() {};

Factory::~Factory() {};

void Factory::Initialize(ResourceAllocator* pRessourceAllocator)
{
	m_pRessourceAllocator = pRessourceAllocator;
}