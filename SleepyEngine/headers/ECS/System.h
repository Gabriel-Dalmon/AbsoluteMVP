#pragma once

class Entity;

class System
{
public:
	System();
	~System();

	int Initialize();
	int Update(float deltaTime);
	int Release();

	int AddEntity(Entity* entity);
	int RemoveEntity(Entity* entity);

	//Unsafe
	virtual void UNSAFE_AddEntity(Entity* entity);
	virtual void UNSAFE_RemoveEntity(Entity* entity);

	int GetRequiredComponentsBID() { return m_requiredComponentsBID; };

private:
	int m_requiredComponentsBID;
	//ComponentTypes* requiredComponents;
};