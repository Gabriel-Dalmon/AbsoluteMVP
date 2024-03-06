#pragma once

#include <vector>

class Component;

class Entity
{
private:
	Entity();
	~Entity() {};

	// INIT
	void Init();

public: // Create and kill entity
	static Entity* CreateEmptyEntity();
	void KillSelf();

public: // SETTER / GETTER	
	template<typename T> 
	void AddComponent(T component)   
	{
		if (GetComponent<T>() != nullptr)
			return;

		m_componentsList.push_back(component); 
	}

	template<typename T>
	void RemoveComponent()
	{
		for (int i = 0; i < m_componentsList.size(); i++)
		{
			if (dynamic_cast<T>(m_componentsList[i]) != NULL)
			{
				m_componentsList.erase(m_componentsList.begin() + i);
			}
		}
	}
	
	template<typename T>
	T GetComponent() {
		for (int i = 0; i < m_componentsList.size(); i++)
		{
			if (dynamic_cast<T>(m_componentsList[i]) != NULL)  
			{
				return (T)m_componentsList[i];
			}
		}
		return nullptr; 
	}
	
	// Clear
	void Clear();

private:
	std::vector<Component*> m_componentsList;  
};

