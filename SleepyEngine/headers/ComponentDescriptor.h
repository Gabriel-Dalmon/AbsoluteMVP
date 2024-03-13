#pragma once

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
	std::vector<VertexTexture>* vertices;
	std::vector<int>* indices;
};

struct MeshReferenceDescriptor : Descriptor
{
	Mesh* meshRef;
};

struct ShaderReferenceDescriptor : Descriptor
{
	ID3D12RootSignature* rootSignature;
	ID3D12PipelineState* PSO;
	int offset = 0;
};