#include "ComponentDescriptor.h"
#include "Entity.h"
#include "Factory.h"

#include "pch.h"
//include components
#include "ColliderSphere.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "ShaderReference.h"
#include "RessourceAllocator.h"


Factory::Factory() {};

Factory::~Factory() {};

void Factory::Init(MeshRessources* parseOutpute) 
{
	m_pMeshRessources = parseOutpute;
}


void Factory::FillPlayer(Entity* pEntity)
{
	ColliderSphereDescriptor CSDesc;
	CSDesc.center = { 0, 0, 0 };
	CSDesc.radius = 1;
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	collider->Init(&CSDesc);
	pEntity->AddComponent<ColliderSphere*>(collider);


	MeshReferenceDescriptor MeshRefDesc;
	//MDesc->MeshRef = ressourceAllocator->mesCollection("cube")
	/*MeshReference* meshRef = Component::CreateComponent<MeshReference>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<Mesh*>(meshRef);*/

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