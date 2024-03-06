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
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	pEntity->AddComponent<ColliderSphere*>(collider);

	MeshRenderer* mesh = Component::CreateComponent<MeshRenderer>();
	pEntity->AddComponent<MeshRenderer*>(mesh);

	/*ShaderReference* shaderReference;
	shaderReference->Init();
	player->AddComponent<ShaderReference*>(shaderReference);*/

	//shoot script here
};


void Factory::FillEnemy(Entity* pEntity)
{

};


void Factory::FillBullet(Entity* pEntity) 
{

};