#pragma once

const CD3DX12_STATIC_SAMPLER_DESC biLinearWrap(
	0, // shaderRegister
	D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
	D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
	D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
	D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

class ShaderTexture : public Shader
{
public:
	ShaderTexture() {};
	~ShaderTexture() {};
	void Init();
};