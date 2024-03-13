#include "pch.h"

void ShaderColor::Initialize(Device* m_pDevice)
{
	CreateRootSignature(m_pDevice);
	CompileVertexShader(L"Shaders/Color.hlsl");
	CompilePixelShader(L"Shaders/Color.hlsl");
	CreatePipelineStateObject(m_pDevice);
	m_pInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
}

void ShaderColor::CreateRootSignature(Device* pDevice)
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];
	slotRootParameter[0].InitAsConstantBufferView(0);

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	ID3DBlob* pSerializedRootSig = nullptr;
	ThrowIfFailed(D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSerializedRootSig, NULL));

	// Create the root signature
	ThrowIfFailed(pDevice->GetD3DDevice()->CreateRootSignature(
		0,
		pSerializedRootSig->GetBufferPointer(),
		pSerializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature))
	);
}

