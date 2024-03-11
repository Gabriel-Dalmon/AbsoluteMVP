#include "pch.h"


ShaderReference::ShaderReference()
{
}

void ShaderReference::Initialize()
{
}

void ShaderReference::Release()
{
	RELEASE(m_pShader);
}

