#include "pch.h"
#include "Component.h"

//#include "Entity.h"

Component::Component()
{
}

void Component::Release()
{
	delete this;
}