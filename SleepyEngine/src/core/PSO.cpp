#include "pch.h"

#include "PSO.h"

ID3D12PipelineState* InitPSO(std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout,
	ID3D12RootSignature* pRootSignature, 
	ID3DBlob* pVSByteCode, 
	ID3DBlob* pPSByteCode, 
	DXGI_FORMAT backBufferFormat,
	bool m4xMsaaState,
	int m4xMsaaQuality,
	DXGI_FORMAT depthStencilFormat,
	ID3D12Device* device,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType)
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC descriptor;
	ZeroMemory(&descriptor, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	descriptor.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
	descriptor.pRootSignature = pRootSignature;
	descriptor.VS =
	{
		(BYTE*)(pVSByteCode->GetBufferPointer()),
		pVSByteCode->GetBufferSize()
	};
	descriptor.PS =
	{
		(BYTE*)(pPSByteCode->GetBufferPointer()),
		pPSByteCode->GetBufferSize()
	};

	descriptor.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	descriptor.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	descriptor.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	descriptor.SampleMask = UINT_MAX;
	descriptor.PrimitiveTopologyType = topologyType;
	descriptor.NumRenderTargets = 1;
	descriptor.RTVFormats[0] = backBufferFormat;
	descriptor.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	descriptor.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	descriptor.DSVFormat = depthStencilFormat;

	ID3D12PipelineState* PSO;
	device->CreateGraphicsPipelineState(&descriptor, IID_PPV_ARGS(&PSO));
	
	return PSO;
}


void DeletePSO(ID3D12PipelineState* pso)
{

}