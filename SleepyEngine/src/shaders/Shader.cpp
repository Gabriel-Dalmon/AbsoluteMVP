#include "pch.h"
#include "Shader.h"

Shader::Shader()
{
	m_pVSByteCode = nullptr;
	m_pPSByteCode = nullptr;
}

void Shader::Init()
{  	
	CD3DX12_ROOT_PARAMETER slotRootParameter[1]; 
	slotRootParameter[0].InitAsConstantBufferView(0);    

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &m_pSerializedRootSig, NULL);

	// ThrowIfFailed(x) page 234
}

ID3DBlob* Shader::CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target)
{
	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = S_OK;

	ID3DBlob* byteCode = nullptr;
	ID3DBlob* errors;
	hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	std::vector<D3D12_INPUT_ELEMENT_DESC> m_pInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};


	// ThrowIfFailed(x)
	if (hr != S_OK)
	{
		std::cout << "HR MARCHE PAS !!!" << std::endl;
		return nullptr;
	}

	return byteCode;
}

void Shader::Release()
{
	RELEASE(m_pVSByteCode);
	RELEASE(m_pPSByteCode);
}

void Shader::CompileVS(std::wstring fileName)  
{
	m_pVSByteCode = CompileShader(fileName, nullptr, "VS", "vs_5_0");
}

void Shader::CompilePS(std::wstring fileName)
{
	m_pVSByteCode = CompileShader(fileName, nullptr, "PS", "ps_5_0");
}
