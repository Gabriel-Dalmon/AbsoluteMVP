#pragma once
#include <concepts>

class GameState;

class SleepyEngine
{
public:
	SleepyEngine();
	~SleepyEngine();

	template<typename T>
	int Initialize()
	{
		m_pCurrentGameState = dynamic_cast<GameState>(new T);
		if (m_pCurrentGameState == nullptr) // GameState must have a virtual method
		{
			MessageBox(nullptr, "The default GameState type passed during the engine initialization is invalid. It should inherit the GameState class.", L"INITIALIZATION ERROR", MB_OK);
			return -1;
		}
		m_pCurrentGameState->Initialize();
		return 0;
	};
	int Run();
	int SwitchGameState();
	int Shutdown();
	int Release();

private:
	GameState* m_pCurrentGameState;
	bool m_isRunning = false;
};