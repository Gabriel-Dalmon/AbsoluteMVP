#include "pch.h"

Entity* GameFactory::CreateEmptyEntity()
{
	Entity* entity = Entity::CreateEmptyEntity();
	return entity;
}

void GameFactory::FillPlayer(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->SetVelocity(0.0f, 0.0f, 0.0f);

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

	// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 1;
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);

	//MeshRenderer* test = pEntity->GetComponent<MeshRenderer*>();

	//shoot script here
};


void GameFactory::FillEnemy(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->SetVelocity(0.0f, 0.0f, 0.0f);

	ColliderSphereDescriptor CSDesc;
	CSDesc.center = { 0, 0, 0 };
	CSDesc.radius = 1;
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	collider->Init(&CSDesc);
	pEntity->AddComponent<ColliderSphere*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("cube"); // change to an enemy mesh 
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;

	// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 1; // chnage to id of enemy texture
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);
};


void GameFactory::FillBullet(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->SetVelocity(0.0f, 0.0f, 0.0f);

	ColliderSphereDescriptor CSDesc;
	CSDesc.center = { 0, 0, 0 };
	CSDesc.radius = 1;
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	collider->Init(&CSDesc);
	pEntity->AddComponent<ColliderSphere*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->getMesh("cube"); // change to a bullet mesh
	MeshRenderer* meshRef = Component::CreateComponent<MeshRenderer>();
	meshRef->Init(&MeshRefDesc);
	pEntity->AddComponent<MeshRenderer*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;

	// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 1; // change to id of bullet texture
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);
};