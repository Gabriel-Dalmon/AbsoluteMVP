#include "pch.h"

ShaderReference::ShaderReference()
{
}

void ShaderReference::Init(ShaderReferenceDescriptor* desc)
{
	m_pRootSignature = desc->rootSignature;
	m_pPSO = desc->PSO;
	m_texID = desc->id;
}

void ShaderReference::Release()
{
}

