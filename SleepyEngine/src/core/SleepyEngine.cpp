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
	while (true)
	{
		m_pCurrentGameState->Update();
	}
}

int SleepyEngine::SwitchGameState()
{
	return 0;
}
