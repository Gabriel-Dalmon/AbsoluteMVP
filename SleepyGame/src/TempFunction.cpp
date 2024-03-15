#include "pch.h"


TempFunction::TempFunction(HINSTANCE hInstance) : SleepyEngine(hInstance)
{
}

void TempFunction::BlankInit()
{
    
}

void TempFunction::BlankUpdate()
{
}

void TempFunction::BlankPreLoop()
{
    OutputDebugStringA("Attempting to load entities\n");

    /*Entity* player = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillPlayer(player);
    m_entities.push_back(player);
    OutputDebugStringA("entity 'player' loaded\n");

    Entity* enemy = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillEnemy(enemy);
    m_entities.push_back(enemy);
    OutputDebugStringA("entity 'enemy' loaded\n");*/

    Entity* bullet = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillBullet(bullet);
    m_entities.push_back(bullet);
    OutputDebugStringA("entity 'bullet' loaded\n");

    /*Entity* skybox = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillSkybox(skybox);
    m_entities.push_back(skybox);
    OutputDebugStringA("entity 'skybox' loaded\n");*/

    /*Entity* sphere = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillSphere(sphere);
    m_entities.push_back(sphere);
    OutputDebugStringA("entity 'sphere' loaded\n");*/

    OutputDebugStringA("All entities loaded\n");
}


