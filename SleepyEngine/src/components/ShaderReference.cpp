#include "pch.h"

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

