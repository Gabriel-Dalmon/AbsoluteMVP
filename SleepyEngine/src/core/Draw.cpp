#include <d3dx12.h>
#include <DirectXColors.h>

#include "Draw.h"
#include "SleepyEngine.h"
#include "Mesh.h"

//preparez a command list and send it to the command queue
//perhaps not the optimal way to draw stuff
//shouldnt forget to fix it later
void Draw(ID3D12GraphicsCommandList* pCommandList, ID3D12DescriptorHeap* pCBVHeap, ID3D12RootSignature* pRootSignature, Mesh* mesh, ID3D12CommandQueue* pCommandQueue)
{
	pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBufferView(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	pCommandList->ClearRenderTargetView(GetCurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	pCommandList->ClearDepthStencilView(GetDepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	pCommandList->OMSetRenderTargets(1, &GetCurrentBackBufferView(), true, &GetDepthStencilView());

	ID3D12DescriptorHeap* descriptorHeaps[] = { pCBVHeap };
	pCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	pCommandList->SetGraphicsRootSignature(pRootSignature);

	pCommandList->IASetVertexBuffers(0, 1, &mesh->VertexBufferView());
	pCommandList->IASetIndexBuffer(&mesh->IndexBufferView());

	pCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pCommandList->SetGraphicsRootDescriptorTable(0, pCBVHeap->GetGPUDescriptorHandleForHeapStart());

	/* the following code is the one that comse from the book
	* we would like to iterate in the submesh if we had one, maybe later
	*pCommandList->DrawIndexedInstanced(
	*	mesh->DrawArgs["box"].IndexCount,
	*	1, 0, 0, 0);*/

	pCommandList->DrawIndexedInstanced(mesh->m_indexCount, 1, 0, 0, 0);

	pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBufferView(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	pCommandList->Close();

	ID3D12CommandList* cmdsLists[] = { pCommandList };
	pCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	//swap chain
}