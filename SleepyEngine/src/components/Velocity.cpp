#include "pch.h"

void Velocity::SetVelocity(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

XMVECTOR Velocity::GetVelocity()
{
	XMVECTOR vect = { m_x, m_y, m_z, 0.f };
	return vect;
}