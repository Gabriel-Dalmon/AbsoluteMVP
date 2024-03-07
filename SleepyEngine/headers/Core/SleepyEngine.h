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
			// Throw Error / Open Message Box
			return -1;
		}
		m_pCurrentGameState->Initialize();
		return 0;
	};
	int Run();
	int SwitchGameState();

private:
	GameState* m_pCurrentGameState;
};