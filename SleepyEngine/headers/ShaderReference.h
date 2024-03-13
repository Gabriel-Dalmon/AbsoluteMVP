#pragma once

class ShaderReference : public Component 
{
public:
	ShaderReference();
	~ShaderReference() {};

	// INIT
	void Init(ShaderReferenceDescriptor* desc);

	// SETTER / GETTER
	ID3D12RootSignature* GetRootSignature() { return m_pRootSignature; }
	ID3D12PipelineState* GetPSO() { return m_pPSO; }
	int GetTexID() { return m_texID; };

	// Release
	void Release();

private:
	ID3D12RootSignature* m_pRootSignature = nullptr;
	ID3D12PipelineState* m_pPSO = nullptr;
	int m_texID = 0;
};

