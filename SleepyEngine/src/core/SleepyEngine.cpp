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
		m_timer.Update();
		deltaTime = m_timer.GetDeltaTime();

		m_pCurrentGameState->Update(deltaTime);
	}
	Release();
	return 0;
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

int SleepyEngine::Release()
{
	m_pCurrentGameState->Release();
	return 0;
}