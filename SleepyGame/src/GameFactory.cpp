#include "pch.h"
#include "GameFactory.h"

void GameFactory::FillPlayer(Entity* pEntity)
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
	std::cerr << typeid(*meshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;
	ShaderRefDesc.PSO = m_PSOTexture;
	ShaderRefDesc.rootSignature = m_pRootSignatureTexture;
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);

	//MeshRenderer* test = pEntity->GetComponent<MeshRenderer*>();

	//shoot script here
};


void GameFactory::FillEnemy(Entity* pEntity)
{

};


void GameFactory::FillBullet(Entity* pEntity)
{

};