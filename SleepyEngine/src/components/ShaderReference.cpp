#include "pch.h"
#include "ShaderReference.h"
#include "ComponentDescriptor.h"


ShaderReference::ShaderReference()
{
}

void ShaderReference::Init(ShaderReferenceDescriptor* desc)
{
	m_pShader = desc->meshRef;
}

