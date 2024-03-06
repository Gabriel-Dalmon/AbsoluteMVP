#include "Entity.h"
#include "Factory.h"

#include "pch.h"
//include components
#include "ColliderSphere.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "ShaderReference.h"


Factory::Factory() {};

Factory::~Factory() {};

void Factory::Init(MeshRessources* parseOutpute) 
{
	m_pMeshRessources = parseOutpute;
}


void Factory::FillPlayer(Entity* pEntity)
{
	Entity* player;
	player->Init();

	ColliderSphere* collider;
	collider->Init();
	player->AddComponent<ColliderSphere*>(collider);

	Mesh* mesh;
	mesh->Init();
	player->AddComponent<Mesh*>(mesh);

	MeshRenderer* meshRenderer;
	meshRenderer->Init(mesh);
	player->AddComponent<MeshRenderer*>(meshRenderer);

	ShaderReference* shaderReference;
	shaderReference->Init();
	player->AddComponent<ShaderReference*>(shaderReference);

	//shoot script here
};


void Factory::FillEnemy(Entity* pEntity)
{

};


void Factory::FillBullet(Entity* pEntity) 
{

};