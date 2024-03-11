#include "pch.h"

SleepyEngine::SleepyEngine()
{
	m_pTimer = new Timer();
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
		m_pTimer->Update();
		deltaTime = m_pTimer->GetDeltaTime();

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