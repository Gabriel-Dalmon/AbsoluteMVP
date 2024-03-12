#include "pch.h"
#include <typeinfo>


Factory::Factory() {};

Factory::~Factory() {};

void Factory::Init(RessourceAllocator* pRessourceAllocator)
{
	m_pRessourceAllocator = pRessourceAllocator;
}

void Factory::SetSignatureAndPSO(SleepyEngine* pEngine)
{
	m_PSOTexture = pEngine->GetPSOTexture();
	m_PSOColor = pEngine->GetPSOColor();
	m_pRootSignatureTexture = pEngine->GetRootSignatureTexture();
	m_pRootSignatureColor = pEngine->GetRootSignatureColor();
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
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("crate");
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	// /!\ we create a shader dynamically for tests, dont forget to change it
	ShaderReferenceDescriptor ShaderRefDesc;
	ShaderRefDesc.PSO = m_PSOTexture;
	ShaderRefDesc.rootSignature = m_pRootSignatureTexture;
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);

	//MeshRenderer* test = pEntity->GetComponent<MeshRenderer*>();

	//shoot script here
};