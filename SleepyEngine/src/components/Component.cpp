#include "pch.h"
#include "Component.h"

//#include "Entity.h"

Component::Component()
{
}

void Component::KillSelf()
{
	delete this;
}