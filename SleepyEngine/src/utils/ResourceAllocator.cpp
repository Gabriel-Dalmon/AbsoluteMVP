#include "pch.h"



void ResourceAllocator::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
    m_pDevice = device;
    m_pCommandList = commandList;
    m_meshCollection = new std::map<std::string, Mesh*>;
}

Mesh* ResourceAllocator::GetMesh(const std::string& name)
{
    auto it = m_meshCollection->find(name);
    if (it != m_meshCollection->end())
    {
        return it->second;
    }


#if defined (DEBUG) || (_DEBUG)
    std::ifstream file("../SleepyEngine/data/JSONResources.json");
#else
    std::ifstream file("JSONResources.json");
#endif

    Json::Value val;
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, file, &val, &errs)) {
        std::cerr << errs << std::endl;
    }


    if (val[name]["type"] == "texture")
    {
        std::vector<VertexTexture> vertices;
        Json::Value JsonVertices = val[name]["vertices"];
        for (int i = 0; i < JsonVertices.size(); i++)
        {
            vertices.push_back(
                VertexTexture({ XMFLOAT3(
                JsonVertices[i]["coordinates"][0].asFloat(),
                JsonVertices[i]["coordinates"][1].asFloat(),
                JsonVertices[i]["coordinates"][2].asFloat()
                ),
                XMFLOAT2(
                JsonVertices[i]["UV"][0].asFloat(),
                JsonVertices[i]["UV"][1].asFloat()
                ) }));
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
    else if (val[name]["type"] == "color")
    {
        std::vector<VertexColor> vertices;
        Json::Value JsonVertices = val[name]["vertices"];
        for (int i = 0; i < JsonVertices.size(); i++)
        {
            vertices.push_back(
                VertexColor({ XMFLOAT3(
                JsonVertices[i]["coordinates"][0].asFloat(),
                JsonVertices[i]["coordinates"][1].asFloat(),
                JsonVertices[i]["coordinates"][2].asFloat()
                ),
                XMFLOAT4(Colors::White) }));
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

    return nullptr;
}

void ResourceAllocator::Release()
{
    m_meshCollection->clear();
    delete m_meshCollection;
}