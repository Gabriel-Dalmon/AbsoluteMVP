#include "pch.h"


Factory::Factory() {};

Factory::~Factory() {};

void Factory::Init(RessourceAllocator* pRessourceAllocator)
{
	m_pRessourceAllocator = pRessourceAllocator;
}


void Factory::FillPlayer(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	ColliderDescriptor CSDesc;
	CSDesc.radius = 1;
	Collider* collider = Component::CreateComponent<Collider>();
	collider->Init(&CSDesc);
	pEntity->AddComponent<Collider*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("cube");
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	// /!\ we create a shader dynamically for tests, dont forget to change it
	ShaderReferenceDescriptor ShaderRefDesc;
	ShaderRefDesc.shaderRef = new Shader;
	ShaderRefDesc.shaderRef->Init();
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);

	//MeshRenderer* test = pEntity->GetComponent<MeshRenderer*>();

	//shoot script here
};


void Factory::FillEnemy(Entity* pEntity)
{

};


void Factory::FillBullet(Entity* pEntity)
{
	pEntity->m_id = 2;

	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	ColliderDescriptor CSDesc;
	CSDesc.radius = 1;
	Collider* collider = Component::CreateComponent<Collider>();
	collider->Init(&CSDesc);
	pEntity->AddComponent<Collider*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("cube");
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	// /!\ we create a shader dynamically for tests, dont forget to change it
	ShaderReferenceDescriptor ShaderRefDesc;
	ShaderRefDesc.shaderRef = new Shader;
	ShaderRefDesc.shaderRef->Init();
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);


};