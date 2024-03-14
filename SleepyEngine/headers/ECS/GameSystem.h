#pragma once


struct GameEntityData : public SystemEntityData
{
	Script* pScript;
};


class GameSystem : public System
{
public:
	GameSystem() {};
	~GameSystem() {};

	void Initialize();

	void UNSAFE_AddEntity(Entity* entity) override;
	void UNSAFE_RemoveEntity(Entity* entity) override;

	void Update(float deltaTime) override;

private:
	std::vector<GameEntityData*> m_entitiesDataList;
};