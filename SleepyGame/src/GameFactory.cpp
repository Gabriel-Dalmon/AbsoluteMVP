#include "pch.h"

Entity* GameFactory::CreateEmptyEntity()
{
	Entity* entity = Entity::CreateEmptyEntity();
	return entity;
}

void GameFactory::FillPlayer(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Initialize();
	pEntity->AddComponent<Transform*>(transform);

	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->SetVelocity(0.0f, 0.0f, 0.0f);
	pEntity->AddComponent<Velocity*>(velocity);

	ColliderSphereDescriptor CSDesc;
	CSDesc.center = { 0, 0, 0 };
	CSDesc.radius = 1;
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	collider->Initialize(&CSDesc);
	pEntity->AddComponent<ColliderSphere*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->GetMesh("cube");
	MeshReference* meshRef = Component::CreateComponent<MeshReference>();
	meshRef->Initialize(&MeshRefDesc);
	pEntity->AddComponent<MeshReference*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;

	/*// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 1;
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Initialize(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);*/

	//MeshRenderer* test = pEntity->GetComponent<MeshRenderer*>();

	//shoot script here
};


void GameFactory::FillEnemy(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Initialize();
	pEntity->AddComponent<Transform*>(transform);

	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->SetVelocity(0.0f, 0.0f, 0.0f);
	pEntity->AddComponent<Velocity*>(velocity);

	ColliderSphereDescriptor CSDesc;
	CSDesc.center = { 0, 0, 0 };
	CSDesc.radius = 1;
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	collider->Initialize(&CSDesc);
	pEntity->AddComponent<ColliderSphere*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->GetMesh("cube"); // change to an enemy mesh 
	MeshReference* meshRef = Component::CreateComponent<MeshReference>();
	meshRef->Initialize(&MeshRefDesc);
	pEntity->AddComponent<MeshReference*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;

	/*// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 1; // chnage to id of enemy texture
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Initialize(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);*/
};


void GameFactory::FillBullet(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Initialize();
	pEntity->AddComponent<Transform*>(transform);

	VelocityDescriptor velocityDesc;
	velocityDesc.x = 1;
	velocityDesc.y = 1;
	velocityDesc.z = 1;
	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->Initialize(&velocityDesc);
	pEntity->AddComponent<Velocity*>(velocity);

	ColliderSphereDescriptor CSDesc;
	CSDesc.center = { 0, 0, 0 };
	CSDesc.radius = 1;
	ColliderSphere* collider = Component::CreateComponent<ColliderSphere>();
	collider->Initialize(&CSDesc);
	pEntity->AddComponent<ColliderSphere*>(collider);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->GetMesh("cube"); // change to a bullet mesh
	MeshReference* meshRef = Component::CreateComponent<MeshReference>();
	meshRef->Initialize(&MeshRefDesc);
	pEntity->AddComponent<MeshReference*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	ScriptDescriptor scriptDesc;
	scriptDesc.motherEntity = pEntity;
	BulletScript* bulletScript = Component::CreateComponent<BulletScript>();
	bulletScript->Initialize(&scriptDesc);
	pEntity->AddComponent<BulletScript*>(bulletScript);

	ShaderReferenceDescriptor ShaderRefDesc;

	/*// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	//ShaderRefDesc.id = 1; // change to id of bullet texture
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Initialize(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);*/
};


void GameFactory::FillSkybox(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Initialize();
	pEntity->AddComponent<Transform*>(transform);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->GetMesh("sky"); // change to a bullet mesh
	MeshReference* meshRef = Component::CreateComponent<MeshReference>();
	meshRef->Initialize(&MeshRefDesc);
	pEntity->AddComponent<MeshReference*>(meshRef);
	std::cerr << typeid(*meshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;

	// for color only object :
	/*ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;*/

	// for textured object :
	/*ShaderRefDesc.PSO = m_PSOTexture;
	ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 2;
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);*/
};

void GameFactory::FillSphere(Entity* pEntity)
{
	Transform* pTransform = Component::CreateComponent<Transform>();
	pTransform->Initialize();
	pEntity->AddComponent<Transform>(pTransform);

	MeshReferenceDescriptor MeshRefDesc;
	MeshRefDesc.meshRef = m_pRessourceAllocator->CreateSphere(5.0f, 20, 20);
	MeshReference* pMeshRef = Component::CreateComponent<MeshReference>();
	pMeshRef->Initialize(&MeshRefDesc);
	pEntity->AddComponent<MeshReference>(pMeshRef);
	std::cerr << typeid(*pMeshRef).name();

	ShaderReferenceDescriptor ShaderRefDesc;

	/*// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	/*ShaderRefDesc.PSO = m_PSOTexture;
	ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	ShaderRefDesc.id = 2;
	
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Initialize(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);*/
}