#include "pch.h"

System::System()
{
}

System::~System()
{
}

int System::Initialize()
{
    return 0;
}

int System::Update(float deltaTime)
{
    return 0;
}

int System::Release()
{
    return 0;
}

int System::AddEntity(Entity* entity)
{
    if (Sleepy::Utils::CheckFlags(entity->GetCompositionFlags(), m_requiredComponentsFlags))
    {
		UNSAFE_AddEntity(entity);
        return 0;
	}
    return 1; // Invalid entity
}

int System::RemoveEntity(Entity* entity)
{
    if (Sleepy::Utils::CheckFlags(entity->GetCompositionFlags(), m_requiredComponentsFlags))
    {
        UNSAFE_RemoveEntity(entity);
		return 0;
        }
	return 1; // Invalid entity
}
