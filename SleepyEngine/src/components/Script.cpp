#include "pch.h"

Script::Script()
{

}

void Script::Init(ScriptDescriptor* desc)
{
	m_pEntity = desc->motherEntity;
}

void Script::Release()
{
}
