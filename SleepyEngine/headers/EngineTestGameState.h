#pragma once

class EngineTestGameState : public GameState
{
public:
	EngineTestGameState();
	~EngineTestGameState();

	void Enter() override;
	void Exit() override;
};