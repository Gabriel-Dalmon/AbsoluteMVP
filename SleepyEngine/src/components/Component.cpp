#include "pch.h"
#include "ECS/Entity.h"

#include "ECS/Component.h"


Component::Component()
{
}

void Component::Release()
{
	RELEASE(m_pEntity);
}
