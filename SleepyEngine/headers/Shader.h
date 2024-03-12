#pragma once

const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
	0, // shaderRegister
	D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
	D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
	D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
	D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

class Shader
{
public:
	Shader() {};
	~Shader() {};

	// INIT
	virtual void Init() {};

	// COMPILE SHADER
	ID3DBlob* CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);

	// CALLING RELEASE MACRO (pch.h)
	void Release();

//protected:
	// FOR ROOT SIGNATURE
	// Root parameter can be a table, root descriptor or root constants
	ID3DBlob* m_pSerializedRootSig = nullptr;

	// CALLING COMPILE SHADER
	void CompileVS(std::wstring fileName);
	void CompilePS(std::wstring fileName);

	// STOCKING SHADERS BYTE CODE
	ID3DBlob* m_pVSByteCode = nullptr; 
	ID3DBlob* m_pPSByteCode = nullptr; 

	std::vector<D3D12_INPUT_ELEMENT_DESC> m_pInputLayout;
};

class ShaderColor : public Shader
{
public:
	ShaderColor() {};
	~ShaderColor() {};
	void Init();
};

class ShaderTexture : public Shader
{
public:
	ShaderTexture() {};
	~ShaderTexture() {};
	void Init();
};