#include "pch.h"

GameState::GameState()
{
}

/**
* Initializes the game state and its systems. By default a game state is created with a renderer system and gameplay system. 
* The physic system must be manually added.
* @return void
*/
void GameState::Initialize(HINSTANCE hAppInstance, RendererDescriptor* pRendererDescriptor, ResourceAllocator* pResourceAllocator)
{
	Renderer* pRenderer = new Renderer();
	pRenderer->Initialize(hAppInstance, pRendererDescriptor);
	pResourceAllocator->Initialize(pRenderer->GetDevice()->GetD3DDevice(), pRenderer->Get);
	m_systemsList.push_back(pRenderer);

	PhysicHandler* pPhysic = new PhysicHandler();
	pPhysic->Initialize();
	m_systemsList.push_back(pPhysic);

	GameSystem* pGameSys = new GameSystem();
	pGameSys->Initialize();
	m_systemsList.push_back(pGameSys);
}

void GameState::Initialize(GameState* previousGameState)
{
}

void GameState::Update(float deltaTime)
{
	for (System* system : m_systemsList)
	{
		system->Update(deltaTime);
	}
	// delete entities
}

void GameState::Enter()
{
}

void GameState::Exit()
{
}

/*
* Adds an entity to the game state and distributes its components to the expected systems.
* @param Entity* entity
* @return int
*/
int GameState::AddEntity(Entity* entity)
{
	int entityBID = entity->GetCompositionFlags();
	for (System* system : m_systemsList)
	{
		if (Sleepy::Utils::CheckFlags(entityBID, system->GetRequiredComponentsFlags()))
		{
			system->UNSAFE_AddEntity(entity);
		}
	}
	m_entitiesList.push_back(entity);
	return 0;
}

/**
* Removes an entity from the game state and the systems linked to it.
* @param Entity* entity
* @return int
*/
int GameState::RemoveEntity(Entity* entity)
{
	int entityBID = entity->GetCompositionFlags();
	for (int i = 0; i < m_entitiesList.size(); i++)
	{
		if (m_entitiesList[i] == entity)
		{
			RELEASE(m_entitiesList[i]);
			m_entitiesList.erase(m_entitiesList.begin() + i);
		}
	}
	return 0;
}

void GameState::Release()
{
	RELEASE(m_pPreviousGameState);
}


