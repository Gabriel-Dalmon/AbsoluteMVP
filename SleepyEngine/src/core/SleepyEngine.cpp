#include "pch.h"
#include "Core/SleepyEngine.h"
#include "Core/GameState.h"

SleepyEngine::SleepyEngine()
{

}

SleepyEngine::~SleepyEngine()
{

}

int SleepyEngine::Run()
{
	float deltaTime = 0.0f;
	m_isRunning = true;
	while (m_isRunning)
	{
		m_pTime->Update();
		deltaTime = m_pTime->GetDeltaTime();
		m_pCurrentGameState->Update(deltaTime);
	}
	Release();
}

int SleepyEngine::SwitchGameState()
{
	return 0;
}

int SleepyEngine::Shutdown()
{
	m_isRunning = false;
	return 0;
}
