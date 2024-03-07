#pragma once

class Component;

class System
{
public:
	System();
	~System();

	int Initialize();
	int Update();
	int Release();

	int AddComponent(Component* component);
	int RemoveComponent(Component* component);

	//Unsafe
	void UNSAFE_AddComponent(Component* component);
	void UNSAFE_RemoveComponent(Component* component);

private:
	int requiredComponents;
};