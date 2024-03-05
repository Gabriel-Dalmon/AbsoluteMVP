#pragma once

class Entity;

class Component
{
public:
	Component();
	~Component() {};

	// Init
	virtual void Init() {};

	// Update 
	virtual void Update() {};

	// SETTER / GETTER 

	// RELEASE
	void Release();

protected:
	Entity* m_pEntity = nullptr; 
};

