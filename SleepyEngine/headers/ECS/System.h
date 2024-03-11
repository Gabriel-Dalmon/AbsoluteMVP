#pragma once

struct SystemEntityData
{
	Entity* entity;
};

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
	virtual void UNSAFE_AddEntity(Entity* entity) = 0;
	virtual void UNSAFE_RemoveEntity(Entity* entity) = 0;

	int GetRequiredComponentsFlags() { return m_requiredComponentsFlags; };

protected:
	int m_requiredComponentsFlags;
};