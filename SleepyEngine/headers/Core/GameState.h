#pragma once

class GameState
{
public:
	GameState();
	~GameState() {};

	// INIT
	// ResourceAllocator should receive its member variables differently.
	void Initialize(HINSTANCE hAppInstance, RendererDescriptor* pRendererDescriptor, ResourceAllocator* pResourceAllocator, Factory* pECSFactory); 
	void Initialize(GameState* previousGameState);
	
	// The override of this function should only be used to set m_pECSFactory with the parameter. 
	virtual void OnEngineCreated(Factory* pECSFactory) = 0;

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

