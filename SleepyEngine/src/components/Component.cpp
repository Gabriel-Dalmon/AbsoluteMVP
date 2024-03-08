#include "pch.h"

Component::Component()
{
}

void Component::Release()
{
	RELEASE(m_pEntity);
}
