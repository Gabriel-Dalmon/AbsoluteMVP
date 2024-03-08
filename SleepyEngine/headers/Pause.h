#pragma once
#include "Core/GameState.h"

class Pause : public GameState
{
public:
	Pause();
	~Pause() {};

	// INIT 
	// void Init();

	// Setter / Getter
	
	// States
	void Enter() override;
	void Exit() override;


private:

};

