#pragma once

class ShaderReference : public Component 
{
public:
	ShaderReference();
	~ShaderReference() {};

	// INIT
	void Initialize(ShaderReferenceDescriptor* pShaderReferenceDescriptor) {};

	// SETTER / GETTER
	Shader* GetShader() { return m_pShader; }

	// Release
	void Release();

private:
	Shader* m_pShader = nullptr;
};

