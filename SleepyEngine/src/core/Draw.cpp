#include "pch.h"
#include "Draw.h"
#include "SleepyEngine.h"
#include "Mesh.h"

//preparez a command list and send it to the command queue
//perhaps not the optimal way to draw stuff
//shouldnt forget to fix it later
void Draw(ID3D12GraphicsCommandList* pCommandList, ID3D12DescriptorHeap* pCBVHeap, ID3D12RootSignature* pRootSignature, Mesh* mesh, ID3D12CommandQueue* pCommandQueue, SleepyEngine* engine)
{
	CD3DX12_RESOURCE_BARRIER barrier;

	barrier = CD3DX12_RESOURCE_BARRIER::Transition(engine->GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	D3D12_CPU_DESCRIPTOR_HANDLE currentBackBufferView = engine->GetCurrentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE dephtStencilView = engine->GetDepthStencilView();

	// bcareful, may have problems using a single initialization of barrier
	pCommandList->ResourceBarrier(1, &barrier);

	pCommandList->ClearRenderTargetView(currentBackBufferView, Colors::LightSteelBlue, 0, nullptr);
	pCommandList->ClearDepthStencilView(dephtStencilView, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	pCommandList->OMSetRenderTargets(1, &currentBackBufferView, true, &dephtStencilView);

	ID3D12DescriptorHeap* descriptorHeaps[] = { pCBVHeap };
	pCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	pCommandList->SetGraphicsRootSignature(pRootSignature);

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = mesh->VertexBufferView();
	D3D12_INDEX_BUFFER_VIEW indexBufferView = mesh->IndexBufferView();

	pCommandList->IASetVertexBuffers(0, 1, &vertexBufferView);
	pCommandList->IASetIndexBuffer(&indexBufferView);

	pCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pCommandList->SetGraphicsRootDescriptorTable(0, pCBVHeap->GetGPUDescriptorHandleForHeapStart());

	/* the following code is the one that comse from the book
	* we would like to iterate in the submesh if we had one, maybe later
	*pCommandList->DrawIndexedInstanced(
	*	mesh->DrawArgs["box"].IndexCount,
	*	1, 0, 0, 0);*/

	pCommandList->DrawIndexedInstanced(mesh->m_indexCount, 1, 0, 0, 0);

	barrier = CD3DX12_RESOURCE_BARRIER::Transition(engine->GetCurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	pCommandList->ResourceBarrier(1, &barrier);

	pCommandList->Close();

	ID3D12CommandList* cmdsLists[] = { pCommandList };
	pCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	//swap chain
}
