#include "pch.h"
#include <json/json.h>



void RessourceAllocator::Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	m_pDevice = device;
	m_pCommandList = commandList;
    m_meshCollection = new std::map<std::string, Mesh*>;
}

Mesh* RessourceAllocator::getMesh(const std::string& name)
{
	auto it = m_meshCollection->find(name);
	if (it != m_meshCollection->end())
	{
		return it->second;
	}

    
#if defined (DEBUG) || (_DEBUG)
    std::ifstream file("../SleepyEngine/JSONRessources.json");
#else
    std::ifstream file("JSONRessources.json");
#endif

    Json::Value val;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    JSONCPP_STRING errs;
    
    if (!parseFromStream(builder, file, &val, &errs)) {
        std::cerr << errs << std::endl;
    }

    std::vector<Vertex> vertices;
    Json::Value JsonVertices = val[name]["vertices"];
    for (int i = 0; i < JsonVertices.size(); i++) 
    {
        vertices.push_back(
            Vertex({ XMFLOAT3(
            JsonVertices[i]["coordinates"][0].asFloat(), 
            JsonVertices[i]["coordinates"][1].asFloat(), 
            JsonVertices[i]["coordinates"][2].asFloat()
            ), 
            XMFLOAT2(
            JsonVertices[i]["color"][0].asFloat(),
            JsonVertices[i]["color"][1].asFloat()
            )}));
    }

    std::vector<uint16_t> indices;
    Json::Value JsonIndices = val[name]["indices"];
    for (int i = 0; i < JsonIndices.size(); i++)
    {
        indices.push_back(JsonIndices[i].asFloat());
    }

	Mesh* mesh = new Mesh();

	mesh->Init(m_pDevice, m_pCommandList, &vertices, &indices);
    m_meshCollection->insert(std::pair<std::string, Mesh*>(name, mesh));

	return mesh;
}

void RessourceAllocator::Release()
{
    m_meshCollection->clear();
    delete m_meshCollection;
}