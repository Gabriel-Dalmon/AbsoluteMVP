#pragma once

class GameTestGameState : public GameState
{
public:
	GameTestGameState();
	~GameTestGameState();

	void Enter() override;
	void Exit() override;
};