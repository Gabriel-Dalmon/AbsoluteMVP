#pragma once
#include "Component.h"

class Shader;

class ShaderReference : public Component 
{
public:
	ShaderReference();
	~ShaderReference() {};

	// INIT
	void Init();

	// SETTER / GETTER
	Shader* GetShader() { return m_pShader; }

private:
	Shader* m_pShader = nullptr;
};

