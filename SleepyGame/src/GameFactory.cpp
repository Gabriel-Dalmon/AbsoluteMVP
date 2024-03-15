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


void GameFactory::FillEnemy(Entity* pEntity)
{

};


void GameFactory::FillBullet(Entity* pEntity)
{
	Transform* transform = Component::CreateComponent<Transform>();
	transform->Identity();
	pEntity->AddComponent<Transform*>(transform);

	VelocityDescriptor velocityDesc;
	velocityDesc.x = 1;
	velocityDesc.y = 1;
	velocityDesc.z = 1;
	Velocity* velocity = Component::CreateComponent<Velocity>();
	velocity->Init(&velocityDesc);
	pEntity->AddComponent<Velocity*>(velocity);

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

	ScriptDescriptor scriptDesc;
	scriptDesc.motherEntity = pEntity;
	BulletScript* bulletScript = Component::CreateComponent<BulletScript>();
	bulletScript->Init(&scriptDesc);
	pEntity->AddComponent<BulletScript*>(bulletScript);

	ShaderReferenceDescriptor ShaderRefDesc;

	// for color only object :
	ShaderRefDesc.PSO = m_PSOColor;
	ShaderRefDesc.rootSignature = m_pRootSignatureColor;

	// for textured object :
	//ShaderRefDesc.PSO = m_PSOTexture;
	//ShaderRefDesc.rootSignature = m_pRootSignatureTexture;

	//ShaderRefDesc.id = 1; // change to id of bullet texture
	ShaderReference* shaderReference = Component::CreateComponent<ShaderReference>();
	shaderReference->Init(&ShaderRefDesc);
	pEntity->AddComponent<ShaderReference*>(shaderReference);
};