#include "pch.h"

Entity* GameFactory::CreateEmptyEntity()
{
	Entity* entity = Entity::CreateEmptyEntity();
	return entity;
}

void GameFactory::FillPlayer(Entity* pEntity)
{



	//MeshRenderer* test = pEntity->GetComponent<MeshRenderer*>();

	//shoot script here
};


void GameFactory::FillEnemy(Entity* pEntity)
{

};


void GameFactory::FillBullet(Entity* pEntity)
{

};