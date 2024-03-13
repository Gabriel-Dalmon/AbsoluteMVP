#pragma once

class ShaderColor : public Shader
{
public:
	ShaderColor() {};
	~ShaderColor() {};
	void Initialize(Device* m_pDevice) override;
	void CreateRootSignature(Device* pDevice) override;
};