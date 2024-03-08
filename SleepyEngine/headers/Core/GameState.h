#pragma once

class System;

class GameState
{
public:
	GameState();
	~GameState() {};

	// INIT
	void Initialize();

	// SETTER / GETTER
	GameState* PreviousGameState() { return m_pPreviousGameState; }

	// Update
	void Update(float deltaTime);

	// States
	virtual void Enter();
	virtual void Exit();

	// Entities
	void AddEntity(Entity* entity); 
	void RemoveEntity(Entity* entity);
	bool CheckEntity(Entity* entity);

	// Release
	void Release();
	
private:
	std::vector<Entity*> m_entitiesList;
	std::vector<System*> m_systemsList;

	// States
	GameState* m_pPreviousGameState = nullptr;
};

