#include "pch.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

int Shader::Initialize(Device* pDevice)
{
	CompileShader(L"Shaders/Default.hlsl", nullptr, "VS", "vs_5_0");
	CreateRootSignature(pDevice);
	return 0;
}

int Shader::Release()
{
	return 0;
}

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
		std::cout << "HR MARCHE PAS !!!" << std::endl;
		return nullptr;
	}

	return byteCode;
}

int Shader::CreateRootSignature(Device* pDevice)
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];
	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);
	//slotRootParameter[0].InitAsConstantBufferView(0);    

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	ID3DBlob* pSerializedRootSig = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSerializedRootSig, NULL);

	ThrowIfFailed(pDevice->GetD3DDevice()->CreateRootSignature(
		0,
		pSerializedRootSig->GetBufferPointer(),
		pSerializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature))
	);
	return 0;
}

int Shader::CreateShaders()
{

	return 0;
}

int Shader::CreatePSO()
{
	return 0;
}
