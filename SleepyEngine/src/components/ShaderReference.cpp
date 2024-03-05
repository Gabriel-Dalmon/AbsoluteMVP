#include "pch.h"
#include "Shader.h"

#include "ShaderReference.h"


ShaderReference::ShaderReference()
{
}

void ShaderReference::Init()
{
}

void ShaderReference::Release()
{
	RELEASE(m_pShader);
}

