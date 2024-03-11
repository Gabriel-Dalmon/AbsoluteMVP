#pragma once

class Shader
{
public:
	Shader();
	~Shader();

	int Initialize(Device* pDevice);
	int Release();

protected:
	ID3DBlob* CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);


private:
	int CreateRootSignature(Device* pDevice);
	int CreateShaders();
	int CreatePSO();

private:
	ID3D12RootSignature* m_pRootSignature = nullptr;
	ID3D12PipelineState* m_pPipelineState = nullptr;
};