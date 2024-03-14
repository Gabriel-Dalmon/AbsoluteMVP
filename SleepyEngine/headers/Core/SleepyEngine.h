#pragma once

class SleepyEngine
{
public:
	SleepyEngine();
	~SleepyEngine();

	template<typename GameStateChildType, typename ECSFactoryChildType>
	int Initialize(HINSTANCE hAppInstance, RendererDescriptor* pRendererDescriptor)
	{
		// Should replace these runtime checks with concepts and requires clauses.
		m_pCurrentGameState = dynamic_cast<GameState*>(new GameStateChildType());
		m_pECSFactory = dynamic_cast<Factory*>(new ECSFactoryChildType());
		if (m_pCurrentGameState == nullptr || m_pECSFactory == nullptr)
		{
			MessageBox(
				nullptr, 
				L"The types passed as templates are invalid. They should inherit the default GameState and Factory classes.", 
				L"INITIALIZATION ERROR", 
				MB_OK
			);
			return -1;
		}
		m_pCurrentGameState->Initialize(hAppInstance, pRendererDescriptor, m_pResourceAllocator);
		m_pTimer->Initialize();
		return 0;
	};
	int Run();
	int SwitchGameState();
	int Shutdown();
	int Release();

private:
	GameState* m_pCurrentGameState = nullptr;
	Factory* m_pECSFactory = nullptr;
	ResourceAllocator* m_pResourceAllocator = nullptr;
	Timer* m_pTimer = nullptr;
	bool m_isRunning = false;
};