#pragma once

struct ID3D12GraphicsCommandList;
struct ID3D12DescriptorHeap;
struct ID3D12RootSignature;
class Mesh;

void Draw(ID3D12GraphicsCommandList* pCommandList, ID3D12DescriptorHeap* pCBVHeap, ID3D12RootSignature* pRootSignature, Mesh* mesh);