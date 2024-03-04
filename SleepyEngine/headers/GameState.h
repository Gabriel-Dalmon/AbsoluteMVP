#pragma once

class GameState
{
public:
	GameState();
	~GameState() {};

	// INIT
	void Init();

	// SETTER / GETTER
	GameState* PreviousGameState() { return m_pPreviousGameState; }

	// Update
	void Update();

	// States
	virtual void Enter();
	virtual void Exit();

	// Entities
	void AddEntity(Entity* entity); 
	void RemoveEntity(Entity* entity);
	bool CheckEntity(Entity* entity);
	
private:
	std::vector<Entity*> m_EntityList;
	std::vector<int> m_SystemList;

	// States
	GameState* m_pPreviousGameState = nullptr;
};

