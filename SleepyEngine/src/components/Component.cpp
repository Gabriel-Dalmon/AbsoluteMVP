#include "pch.h"
#include "Entity.h"

#include "Component.h"


Component::Component()
{
}

void Component::Release()
{
	RELEASE(m_pEntity);
}
