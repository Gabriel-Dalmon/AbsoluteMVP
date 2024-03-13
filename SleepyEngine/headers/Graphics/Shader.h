#pragma once

class Shader
{
public:
	Shader() {};
	~Shader() {};

	// INIT
	virtual void Initialize(Device* device) = 0;
	virtual void CreateRootSignature(Device* device) = 0;
	ID3DBlob* CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);
	void CreatePipelineStateObject(Device* pDevice);

	// CALLING RELEASE MACRO (pch.h)
	void Release();

public:
	// GETTERS
	inline ID3D12PipelineState* GetPipelineStateObject()const { return m_pPSO; };
	inline ID3D12RootSignature* GetRootSignature()const { return m_pRootSignature; };

protected:
		// FOR ROOT SIGNATURE
		// Root parameter can be a table, root descriptor or root constants
	ID3DBlob* m_pSerializedRootSig = nullptr;

	// CALLING COMPILE SHADER
	void CompileVertexShader(std::wstring fileName);
	void CompilePixelShader(std::wstring fileName);

	// STOCKING SHADERS BYTE CODE
	ID3DBlob* m_pVSByteCode = nullptr;
	ID3DBlob* m_pPSByteCode = nullptr;

	ID3D12RootSignature* m_pRootSignature = nullptr;
	ID3D12PipelineState* m_pPSO = nullptr;

	std::vector<D3D12_INPUT_ELEMENT_DESC> m_pInputLayout;
};