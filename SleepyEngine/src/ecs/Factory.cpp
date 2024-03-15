#include "pch.h"

Factory::Factory() {};

Factory::~Factory() {};

void Factory::Initialize(ResourceAllocator* pRessourceAllocator, ShaderColor* pShaderColor)
{
	m_pRessourceAllocator = pRessourceAllocator;
	m_pShaderColor = pShaderColor;
}