#include "Shader.h"
#include "D3DUtils.h"

using namespace DirectX;


Shader::Shader()
{
}

void Shader::Release()
{
	RELEASE(m_pVSByteCode);
	RELEASE(m_pPSByteCode);
}

void Shader::CompileVS(std::wstring fileName)  
{
	m_pVSByteCode = D3DUtils::CompileFromFile(fileName, nullptr, "VS", "vs_5_0");
}

void Shader::CompilePS(std::wstring fileName)
{
	m_pVSByteCode = D3DUtils::CompileFromFile(fileName, nullptr, "PS", "ps_5_0");
}
