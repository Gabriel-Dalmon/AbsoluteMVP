#include "pch.h"

#include "TempFunction.h"
#include "../../SleepyEngine/headers/SleepyEngine.h"




void TempFunction::BlankInit()
{
    Entity* bullet = Entity::CreateEmptyEntity();
    ((GameFactory*)m_pFactory)->FillBullet(bullet);
    m_entities.push_back(bullet);
    OutputDebugStringA("entity 'bullet' loaded\n");
}

void TempFunction::BlankUpdate()
{

}


class BulletScript : public Script
{
public:
	BulletScript() {};
	~BulletScript() {};

	// Script class override
	void OnScript() override;

private:
};