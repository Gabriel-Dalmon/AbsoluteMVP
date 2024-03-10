#pragma once

ID3D12PipelineState* InitPSO(std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout,
	ID3D12RootSignature* pRootSignature,
	ID3DBlob* pVSByteCode,
	ID3DBlob* pPSByteCode,
	DXGI_FORMAT backBufferFormat,
	bool m4xMsaaState,
	int m4xMsaaQuality,
	DXGI_FORMAT depthStencilFormat,
	ID3D12Device* device,
	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType);

void DeletePSO(ID3D12PipelineState* pso);