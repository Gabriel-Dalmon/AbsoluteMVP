#pragma once

struct ID3D12GraphicsCommandList;
struct ID3D12DescriptorHeap;
struct ID3D12RootSignature;
class Mesh;
class ID3D12CommandQueue;
class SleepyEngine;

void Draw(ID3D12GraphicsCommandList* pCommandList, ID3D12DescriptorHeap* pCBVHeap, ID3D12RootSignature* pRootSignature, Mesh* mesh, ID3D12CommandQueue* pCommandQueue, SleepyEngine* engine);