#pragma once

#include <DirectXMath.h>
#include <vector>

class ID3D12Device;
class ID3D12GraphicsCommandList;
struct Vertex;
class Mesh;


struct Descriptor {
	ID3D12Device* device;
	ID3D12GraphicsCommandList* commandList;
};

struct ColliderSphereDescriptor : Descriptor
{
	DirectX::XMFLOAT3 center;
	float radius;
};

struct ColliderOBBDescriptor : Descriptor
{
	std::vector<Vertex>* vertices;
	std::vector<int>* indices;
};

struct MeshReferenceDescriptor : Descriptor
{
	Mesh* meshRef;
};

