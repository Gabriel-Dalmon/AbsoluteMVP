#pragma once

struct Descriptor {
	ID3D12Device* device;
	ID3D12GraphicsCommandList* commandList;
};

//struct TransformDescriptor : Descriptor
//{
//
//};

struct ColliderDescriptor : Descriptor
{
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

struct ShaderReferenceDescriptor : Descriptor
{
	Shader* shaderRef;
};