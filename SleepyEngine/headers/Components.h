#pragma once

class Entity;

class Components
{
public:
	Components();
	~Components() {};

	// Init
	virtual void Init() {};

	// Update 
	virtual void Update() {};

	// SETTER / GETTER 


private:
	Entity* m_pEntity; 
};

