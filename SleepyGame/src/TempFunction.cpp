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
    Entity* player = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillPlayer(player);
    m_entities.push_back(player);
    MeshRenderer* temp;
    temp = player->GetComponent<MeshRenderer*>();
    mBoxGeo = temp->GetMesh();
    OutputDebugStringA("entity loaded\n");
}
