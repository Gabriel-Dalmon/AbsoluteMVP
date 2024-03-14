#pragma once

typedef class PlayGameState : public GameState
{
public:
	PlayGameState() {};
	~PlayGameState() {};

	// INIT
	void Initialize();
	void OnEngineCreated(Factory* pECSFactory) override;

	// Entity linked functions
	void CreatePlayer();
	void CreateEnemy();

	void CreateScore();


private:
	GameFactory* m_pGameFactory = nullptr;
}PlayState;
