#include "ComponentDescriptor.h"
#include "Entity.h"
#include "Factory.h"
#include "RessourceAllocator.h"

#include "pch.h"
//include components
#include "ColliderSphere.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Script.h"
#include "ShaderReference.h"
#include "MeshRenderer.h"
#include "Shader.h"


Factory::Factory() {};

Factory::~Factory() {};

void Factory::Init(RessourceAllocator* pRessourceAllocator)
{
	m_pRessourceAllocator = pRessourceAllocator;
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
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("cube");
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);

	// /!\ we create a shader dynamically for tests, dont forget to change it
	ShaderReferenceDescriptor ShaderRefDesc;
	ShaderRefDesc.shaderRef = new Shader;
	ShaderRefDesc.shaderRef->Init();
	ShaderReference* shaderReference;
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);

	//shoot script here
};


void Factory::FillEnemy(Entity* pEntity)
{

};


void Factory::FillBullet(Entity* pEntity) 
{

};