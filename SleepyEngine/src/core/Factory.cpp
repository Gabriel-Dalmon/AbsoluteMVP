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

	Velocity* v = Component::CreateComponent<Velocity>();
	v->Init();
	v->SetVelocity(0.f, 0.f, 0.f);
	pEntity->AddComponent<Velocity*>(v);

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
	pEntity->m_id = 1;

	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	ColliderDescriptor CSDesc;
	CSDesc.radius = 1;
	Collider* collider = Component::CreateComponent<Collider>();
	collider->Init(&CSDesc);
	pEntity->AddComponent<Collider*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("pyramide");
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	Velocity* v = Component::CreateComponent<Velocity>();
	v->Init();
	v->SetVelocity(0.f, 0.f, 0.f);
	pEntity->AddComponent<Velocity*>(v);

	// /!\ we create a shader dynamically for tests, dont forget to change it
	ShaderReferenceDescriptor ShaderRefDesc;
	ShaderRefDesc.shaderRef = new Shader;
	ShaderRefDesc.shaderRef->Init();
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);
};


void Factory::FillBullet(Entity* pEntity)
{
	pEntity->m_id = 2;

	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	Velocity* v = Component::CreateComponent<Velocity>();
	v->Init();
	v->SetVelocity(1.f, 1.f, 1.f);
	pEntity->AddComponent<Velocity*>(v);

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