#include "pch.h"

Collider::Collider()
{

}

void Collider::Init()
{
	int a = 8;
}


void Velocity::Init()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
}

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