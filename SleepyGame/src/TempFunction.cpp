#include "pch.h"
#include "TempFunction.h"

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

    Entity* player = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillPlayer(player);
    m_entities.push_back(player);
    OutputDebugStringA("entity 'player' loaded\n");

    Entity* enemy = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillEnemy(enemy);
    m_entities.push_back(enemy);
    OutputDebugStringA("entity 'enemy' loaded\n");

    Entity* bullet = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillBullet(bullet);
    m_entities.push_back(bullet);
    OutputDebugStringA("entity 'bullet' loaded\n");

    OutputDebugStringA("All entities loaded\n");
}


