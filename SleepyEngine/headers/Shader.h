#pragma once

struct Vertex {
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

class Shader
{
public:
	Shader();
	~Shader() {};

	// INIT
	virtual void Init();

	// COMPILE SHADER
	ID3DBlob* CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);

	// CALLING RELEASE MACRO (pch.h)
	void Release();

protected:
	// FOR ROOT SIGNATURE
	// Root parameter can be a table, root descriptor or root constants
	ID3DBlob* m_pSerializedRootSig = nullptr;
	//ID3DBlob* m_pErrorBlob = nullptr;

	// CALLING COMPILE SHADER
	void CompileVS(std::wstring fileName);
	void CompilePS(std::wstring fileName);

	// STOCKING SHADERS BYTE CODE
	ID3DBlob* m_pVSByteCode; 
	ID3DBlob* m_pPSByteCode; 
};

