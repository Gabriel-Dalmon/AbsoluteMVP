#pragma once

class Entity;

class Component
{
public:
	Component();
	~Component() {};

	// Init
	virtual void Init() {};

	// SETTER / GETTER 


private:
	Entity* m_pEntity; 
};

