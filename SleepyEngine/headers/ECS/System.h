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

private:
	int requiredComponents;
};