#include "pch.h"


ShaderReference::ShaderReference()
{
	m_typeFlag = SHADER_REFERENCE;
}

void ShaderReference::Initialize(ShaderReferenceDescriptor* pShaderReferenceDescriptor)
{
	m_pShader = pShaderReferenceDescriptor->pShader;
}

void ShaderReference::Release()
{
	RELEASE(m_pShader);
}

