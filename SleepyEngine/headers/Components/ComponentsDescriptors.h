#pragma once

struct Descriptor {
	ID3D12Device* device;
	ID3D12GraphicsCommandList* commandList;
};

struct TransformDescriptor : Descriptor
{
	float x = 0;
	float y = 0;
	float z = 0;
};

struct ColliderDescriptor : Descriptor
{
	float radius;
};

struct ColliderSphereDescriptor : Descriptor
{
	DirectX::XMFLOAT3 center;
	float radius;
};

struct ColliderOBBDescriptor : Descriptor
{
	std::vector<VertexTexture>* vertices;
	std::vector<int>* indices;
};

struct MeshReferenceDescriptor : Descriptor
{
	Mesh* pMeshReference;
};

struct ShaderReferenceDescriptor : Descriptor
{
	ShaderColor* pShader;
	int id = 0;
};

struct VelocityDescriptor
{
	float x = 0;
	float y = 0;
	float z = 0;
};

struct ScriptDescriptor : Descriptor
{
	Entity* motherEntity;
};