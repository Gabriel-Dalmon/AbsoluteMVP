#include "pch.h"


void RessourceAllocator::Init(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	m_pDevice = device;
	m_pCommandList = commandList;
}

Mesh* RessourceAllocator::getMesh(const std::string& fileName)
{
	auto it = m_meshCollection.find(fileName);
	if (it != m_meshCollection.end())
	{
		return it->second;
	}

	Mesh* mesh = new Mesh();
	//load from json here, lets have a default cube for now
    std::vector<Vertex> vertices =
    {
        Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
        Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
        Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
        Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
        Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
        Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
        Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
        Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
    };

    std::vector<uint16_t> indices =
    {
        // front face
        0, 1, 2,
        0, 2, 3,

        // back face
        4, 6, 5,
        4, 7, 6,

        // left face
        4, 5, 1,
        4, 1, 0,

        // right face
        3, 2, 6,
        3, 6, 7,

        // top face
        1, 5, 6,
        1, 6, 2,

        // bottom face
        4, 0, 3,
        4, 3, 7
    };

	mesh->Init(m_pDevice, m_pCommandList, &vertices, &indices);
	//texture->loadFromFile("data/assets/graphics/images/" + fileName);
	//textures[fileName] = texture;

	return mesh;
}