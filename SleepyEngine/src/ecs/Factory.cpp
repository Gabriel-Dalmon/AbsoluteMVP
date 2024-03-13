#include "pch.h"

Factory::Factory() {};

Factory::~Factory() {};

void Factory::Initialize(ResourceAllocator* pRessourceAllocator)
{
	m_pRessourceAllocator = pRessourceAllocator;
}

void Factory::SetSignatureAndPSO(SleepyEngine* pEngine)
{
	m_PSOTexture = pEngine->GetPSOTexture();
	m_PSOColor = pEngine->GetPSOColor();
	m_pRootSignatureTexture = pEngine->GetRootSignatureTexture();
	m_pRootSignatureColor = pEngine->GetRootSignatureColor();
}