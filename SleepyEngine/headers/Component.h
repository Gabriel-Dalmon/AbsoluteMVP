#pragma once

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
	static Component* CreateComponent() {
		new T;
		T->Init();
		return T;
	}
	void KillSelf();

	// Update 
	virtual void Update() {};

	// SETTER / GETTER 


protected:
	Entity* m_pEntity = nullptr; 
};

