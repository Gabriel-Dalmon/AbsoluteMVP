#include "pch.h"

SleepyEngine::SleepyEngine()
{
	m_pTimer = new Timer();
	m_pResourceAllocator = new ResourceAllocator();
}

SleepyEngine::~SleepyEngine()
{

}

int SleepyEngine::Run()
{
	float deltaTime = 0.0f;
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			m_pTimer->Update();
			deltaTime = m_pTimer->GetDeltaTime();

			m_pCurrentGameState->Update(deltaTime);
		}
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