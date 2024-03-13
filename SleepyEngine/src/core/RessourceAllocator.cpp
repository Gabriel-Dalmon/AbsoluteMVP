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


    if(val[name]["type"] == "texture")
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

Mesh* RessourceAllocator::CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount)
{
    Submesh meshData;

    Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    meshData.Vertices.push_back(topVertex);

    float phiStep = XM_PI / stackCount;
    float thetaStep = 2.0 * XM_PI / sliceCount;
    
    for (int i = 1; i <= stackCount - 1; i++)
    {
        float phi = i * phiStep;

        for (int j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            Vertex vertex;

            vertex.Position.x = radius * sinf(phi) * cosf(theta);
            vertex.Position.y = radius * cosf(phi);
            vertex.Position.z = radius * sinf(phi) * sinf(theta);

            vertex.TangentU.x = -radius * sinf(phi) * sinf(theta);
            vertex.TangentU.y = 0.0f;
            vertex.TangentU.z = +radius * sinf(phi) * cosf(theta);

            XMVECTOR T = XMLoadFloat3(&vertex.TangentU);
            XMStoreFloat3(&vertex.TangentU, XMVector3Normalize(T));

            XMVECTOR p = XMLoadFloat3(&vertex.Position);
            XMStoreFloat3(&vertex.Position, XMVector3Normalize(p));

            vertex.TexC.x = theta / XM_2PI;
            vertex.TexC.y = phi / XM_PI;

            meshData.Vertices.push_back(vertex);

        }
    }

    meshData.Vertices.push_back(bottomVertex);

    for (int i = 1; i < sliceCount; i++)
    {
        meshData.Indices.push_back(0);
        meshData.Indices.push_back(i + 1);
        meshData.Indices.push_back(i);
    }

    int baseIndex = 1;
    int ringVertexCount = sliceCount + 1;

    for (int i = 0; i < stackCount - 2; i++)
    {
        for (int j = 0; j < sliceCount; j++)
        {
            meshData.Indices.push_back(baseIndex + i * ringVertexCount + j);
            meshData.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            meshData.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            meshData.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            meshData.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            meshData.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }

    uint32_t southPoleIndex = (uint32_t)meshData.Vertices.size() - 1;

    baseIndex = southPoleIndex - ringVertexCount;

    for (int i = 0; i < sliceCount; i++)
    {
        meshData.Indices.push_back(southPoleIndex);
        meshData.Indices.push_back(baseIndex + i);
        meshData.Indices.push_back(baseIndex + i + 1);
    }

    Mesh* mesh = new Mesh();
    mesh->Init(m_pDevice, m_pCommandList, &meshData.Vertices, &meshData.GetIndices16()); 

    m_meshCollection->insert(std::pair<std::string, Mesh*>("sphere", mesh));

    return mesh; 
}

void RessourceAllocator::Release()
{
    m_meshCollection->clear();
    delete m_meshCollection;
}