#pragma once

class Component
{
protected:
	Component();
	~Component() {};


public:
	virtual void Initialize() {};
	virtual void Update() {};

	// SETTER / GETTER 

	void Release();

	template<typename T>
	static T* CreateComponent() {
		T* component = new T;
		return component;
	}

	template<typename T, typename U>
	static T* CreateComponent(U* descriptor) {
		T* component = new T;
		component->Initialize(descriptor);
		return component;
	}

protected:
	Entity* m_pEntity = nullptr; 
};

