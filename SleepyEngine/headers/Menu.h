#pragma once

class Menu : public GameState
{
public:
	Menu();
	~Menu() {};

	// Init
	// void Init();

	// States
	void Enter() override;
	void Exit() override;
};

