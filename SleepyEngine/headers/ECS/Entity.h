#pragma once

class Entity
{
public:
	Entity();
	~Entity() {};
	static Entity* CreateEmptyEntity();

	void Initialize();
	void Release();


	// SETTER / GETTER
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
	T* GetComponent() {
		for (int i = 0; i < m_componentsList.size(); i++)
		{
			if (dynamic_cast<T*>(m_componentsList[i]) != NULL)  
			{
				return (T*)m_componentsList[i];
			}
		}
		return nullptr; 
	}

public: // SETTER / GETTER	
	template<typename T>
	void AddComponent(T component)
	{
		if (GetComponent<T>() != nullptr)
			return;

		m_componentsList.push_back((Component*)component);
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

	// Parent entity
	Entity* GetParent();
	void SetParent(Entity* parent);
	void RemoveParent();

	// Child entity
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	std::vector<Entity*> GetChildren();

int GetCompositionFlags() { return m_compositionFlags; };

private:
	std::vector<Component*> m_componentsList;  
	int m_compositionFlags;
	std::vector<Entity*> m_ChildrenEntities;
	Entity* m_pParentEntity = nullptr;
};

