#pragma once
#include "DirectXMath.h"

#include "Entity.h"

using namespace DirectX;


class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	void Init(XMVECTOR velocity);

	XMFLOAT3 m_velocity;

	/*MeshRenderer* m_pMeshRenderer;
	Texture* m_pTexture;
	ColliderSphere* m_pCollider;*/
};