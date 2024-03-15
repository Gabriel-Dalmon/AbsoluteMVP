#pragma once


struct PhysicEntityData : public SystemEntityData
{
	Transform* pTransform;
	Collider* pCollider;
};


class PhysicSystem : public System
{
public:
	PhysicSystem() {};
	~PhysicSystem() {};

	void Initialize();

	void UNSAFE_AddEntity(Entity* entity) override;
	void UNSAFE_RemoveEntity(Entity* entity) override;

	void Update(float deltaTime) override;

private:
	bool CheckCollision(PhysicEntityData* self, PhysicEntityData* target);

	std::vector<PhysicEntityData*> m_entitiesDataList;
};