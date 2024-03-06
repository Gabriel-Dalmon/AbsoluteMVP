#pragma once
#include <map>
#include <string>

struct Vertex;

struct MeshRessources
{
	Vertex* vertices;
	int* indices;
};

std::map<std::string, MeshRessources>* ExtractJson(char* file);