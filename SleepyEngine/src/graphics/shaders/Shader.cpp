#include "pch.h"

ID3DBlob* Shader::CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target)
{
	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	std::cout << &filename << "  " << filename.c_str() << std::endl;

	HRESULT hr = S_OK;

	ID3DBlob* byteCode = nullptr;
	ID3DBlob* errors;
	hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());


	// ThrowIfFailed(x)
	if (hr != S_OK)
	{
		std::cerr << "HR MARCHE PAS !!!" << std::endl;
		return nullptr;
	}

	return byteCode;
}

void Shader::CreatePipelineStateObject(Device* pDevice)
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC descriptor;
	ZeroMemory(&descriptor, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	descriptor.InputLayout = { m_pInputLayout.data(), (UINT)m_pInputLayout.size() };
	descriptor.pRootSignature = m_pRootSignature;
	descriptor.VS =
	{
		(BYTE*)(m_pVSByteCode->GetBufferPointer()),
		m_pVSByteCode->GetBufferSize()
	};
	descriptor.PS =
	{
		(BYTE*)(m_pPSByteCode->GetBufferPointer()),
		m_pPSByteCode->GetBufferSize()
	};

	descriptor.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	descriptor.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	descriptor.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	descriptor.SampleMask = UINT_MAX;
	descriptor.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	descriptor.NumRenderTargets = 1;
	descriptor.RTVFormats[0] = BACK_BUFFER_FORMAT;
	descriptor.SampleDesc.Count = pDevice->Get4xMSAAState() ? 4 : 1;
	descriptor.SampleDesc.Quality = pDevice->Get4xMSAAState() ? (pDevice->Get4xMSAAQuality() - 1) : 0;
	descriptor.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	pDevice->GetD3DDevice()->CreateGraphicsPipelineState(&descriptor, __uuidof(ID3D12PipelineState), (void**)&m_pPSO);
}

void Shader::Release()
{
	RELEASE(m_pVSByteCode);
	RELEASE(m_pPSByteCode);
	RELEASE(m_pSerializedRootSig);
}

void Shader::CompileVertexShader(std::wstring fileName)
{
	m_pVSByteCode = CompileShader(fileName, nullptr, "VS", "vs_5_0");
}

void Shader::CompilePixelShader(std::wstring fileName)
{
	m_pPSByteCode = CompileShader(fileName, nullptr, "PS", "ps_5_0");
}
