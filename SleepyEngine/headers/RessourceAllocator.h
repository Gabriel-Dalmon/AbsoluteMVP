#pragma once

#include <vector>

class Mesh;

class RessourceAllocator 
{
public:
	RessourceAllocator() {};
	~RessourceAllocator() {};

	void Init();
	void Remove();

public:
	std::vector<Mesh*> m_meshCollection;
};