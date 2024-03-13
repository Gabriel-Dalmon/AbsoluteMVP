#include "pch.h"


ShaderReference::ShaderReference()
{
}

void ShaderReference::Release()
{
	RELEASE(m_pShader);
}

