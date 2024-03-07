#pragma once
#include "ComponentDescriptor.h"

class Entity;

class Component
{
protected:
	Component();
	~Component() {};

	// Init
	virtual void Init() {};

public: // Create and kill component
	template<typename T>
	static T* CreateComponent() {
		T* component = new T;
		return component;
	}

	template<typename T, typename U>
	static T* CreateComponent(U* descriptor) {
		T* component = new T;
		component->Init(descriptor);
		return component;
	}


	void Release();

	// Update 
	virtual void Update() {};

	// SETTER / GETTER 


protected:
	Entity* m_pEntity = nullptr; 
};

