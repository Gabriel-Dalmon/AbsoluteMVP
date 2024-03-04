#pragma once
#include "Component.h"
#include <DirectXCollision.h>

using namespace DirectX;


class Collider :
    public Component
{
public:
    Collider();
    ~Collider();

    virtual void Init() {};
};

