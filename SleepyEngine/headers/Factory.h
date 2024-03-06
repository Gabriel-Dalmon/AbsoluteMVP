#pragma once

class Entity;
struct MeshRessources;

class Factory 
{
public:
	Factory();
	~Factory();
	void Init(MeshRessources* pParseOutpute);

private:
	MeshRessources* m_pMeshRessources;

public:
	void FillPlayer(Entity* pEntity);
	void FillEnemy(Entity* pEntity);
	void FillBullet(Entity* pEntity);
};