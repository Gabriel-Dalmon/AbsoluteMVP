#pragma once

class GameState
{
public:
	GameState();
	~GameState() {};

	// INIT
	void Initialize(HINSTANCE hAppInstance, RendererDescriptor* pRendererDescriptor);
	void Initialize(GameState* previousGameState);

	// SETTER / GETTER
	GameState* GetPreviousGameState() { return m_pPreviousGameState; }

	// Update
	void Update(float deltaTime);

	// States
	virtual void Enter();
	virtual void Exit();

	// Entities
	int AddEntity(Entity* entity);
	int RemoveEntity(Entity* entity);

	// Release
	void Release();
	
private:
	std::vector<Entity*> m_entitiesList;
	std::vector<System*> m_systemsList;

	// States
	GameState* m_pPreviousGameState = nullptr;
};

