#include "pch.h"

void ResourceAllocator::Initialize(Device* pDevice, CommandQueue* pCommandQueue)
{
    m_pDevice = pDevice;
    m_pCommandQueue = pCommandQueue;
    m_meshCollection = new std::map<std::string, Mesh*>;

    ID3D12Device* pD3DDevice = m_pDevice->GetD3DDevice();

    pD3DDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT, 
        __uuidof(ID3D12CommandAllocator), 
        (void**)&m_pCommandAllocator
    );

    pD3DDevice->CreateCommandList(
        0, 
        D3D12_COMMAND_LIST_TYPE_DIRECT, 
        m_pCommandAllocator, 
        nullptr, 
        __uuidof(ID3D12CommandList), 
        (void**)&m_pCommandList
    );
    m_pCommandList->Close();
}

Mesh* ResourceAllocator::GetMesh(const std::string& name)
{
    auto it = m_meshCollection->find(name);
    if (it != m_meshCollection->end())
    {
        return it->second;
    }


#if defined (DEBUG) || (_DEBUG)
    std::ifstream file("C:/Users/gabri/source/repos/yoannklt/Sleepy/SleepyEngine/data/JSONRessources.json");
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

        Mesh* pMesh = CreateMesh(&vertices, &indices);

        m_meshCollection->insert(std::pair<std::string, Mesh*>(name, pMesh));

        return pMesh;
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

        Mesh* pMesh = CreateMesh(&vertices, &indices);

        m_meshCollection->insert(std::pair<std::string, Mesh*>(name, pMesh));

        return pMesh;
    }

    return nullptr;
}

void ResourceAllocator::Release()
{
    m_meshCollection->clear();
    delete m_meshCollection;
}