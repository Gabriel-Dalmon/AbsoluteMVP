#include "Bullet.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "ColliderSphere.h"

Bullet::Bullet() {};

Bullet::~Bullet() {};

void Bullet::Init(XMVECTOR velocity)
{
	XMStoreFloat3(&m_velocity, velocity);

	Mesh mesh;
	mesh.Init();
	AddComponent<Mesh*>(&mesh);

	MeshRenderer meshRenderer;
	meshRenderer.Init(&mesh);
	AddComponent<MeshRenderer*>(&meshRenderer);

	ColliderSphere collider;
	collider.Init();
	AddComponent<ColliderSphere*>(&collider);
}

/*MeshRenderer* m_pMeshRenderer;
	Texture* m_pTexture;
	ColliderSphere* m_pCollider;*/