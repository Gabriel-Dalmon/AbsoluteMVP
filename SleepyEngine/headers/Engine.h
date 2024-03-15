#pragma once

// LIBS
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

// JSON
#include <json/json.h>

// WINDOWS
#include <Windows.h>
#include <windowsx.h>
#include <wrl.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif

// STD
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>
#include <float.h>
#include <cmath>

// DIRECTX
#include <comdef.h> 
#include <dxgi1_4.h>
#include <DXGI.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>



// FORWARD DECLARATIONS
class Utils;
class D3DUtils;
class HResultException;
class MathHelper;

class Mesh;

// COMPONENTS
class Component;

class Transform;
class MeshReference;
class ShaderReference;
class Collider;
class ColliderOBB;
class ColliderSphere;
class Script;
class Velocity;
class Camera;

class Entity;

class Window;
class Device;
class SwapChain;
class CommandQueue;
class FrameResource;
class Shader;
class ShaderColor;

class Timer;
class TmpCamera;

struct SystemEntityData;
class System;

class Factory;
class ResourceAllocator;

struct RendererEntityData;
struct RendererDescriptor;
class Renderer;

class PhysicSystem;

class GameState;
class EngineTestGameState;

class SleepyEngine;


// MACROS
#define RELEASE(p) {if (p){ p->Release(); p = nullptr;}}
#define MAX_LOADSTRING 100


// NAMESPACES
using namespace DirectX;

// STRUCTS
struct Vertex
{
    Vertex() {}
    Vertex(
        const XMFLOAT3& p,
        const XMFLOAT3& n,
        const XMFLOAT3& t,
        const XMFLOAT2& uv) :
        Position(p),
        Normal(n),
        TangentU(t),
        TexC(uv) {}
    Vertex(
        float px, float py, float pz,
        float nx, float ny, float nz,
        float tx, float ty, float tz,
        float u, float v) :
        Position(px, py, pz),
        Normal(nx, ny, nz),
        TangentU(tx, ty, tz),
        TexC(u, v) {}

    XMFLOAT3 Position = {0,0,0};
    XMFLOAT3 Normal = { 0,0,0 };
    XMFLOAT3 TangentU = { 0,0,0 };
    XMFLOAT2 TexC = { 0,0 };
};

struct VertexColor
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct VertexTexture
{
	XMFLOAT3 Pos;
	XMFLOAT2 Uv;
};

// Classes 
#include "Resource.h"
#include "Utils/d3dx12.h"
#include "Utils/Utils.h"
using namespace Sleepy;

#include "Utils/D3DUtils.h"
#include "Utils/MathHelper.h"
#include "Utils/HResultException.h"
#include "Utils/Constants.h"

#include "Utils/UploadBuffer.h"

#include "Components/ComponentsDescriptors.h"
#include "ECS/Component.h"
#include "Components/Transform.h"
#include "Components/MeshReference.h"
#include "Components/ShaderReference.h"
#include "Components/Collider.h"
#include "Components/ColliderOBB.h"
#include "Components/ColliderSphere.h"
#include "Components/Script.h"
#include "Components/Velocity.h"
#include "Components/Camera.h"

#include "ECS/Entity.h"

#include "Graphics/Window.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Graphics/FrameResource.h"
#include "Graphics/CommandQueue.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderColor.h"

#include "Mesh.h"


#include "ECS/System.h"
#include "Graphics/Renderer.h"
#include "ECS/PhysicSystem.h"
#include "ECS/GameplaySystem.h"

#include "ECS/Factory.h"
#include "Utils/ResourceAllocator.h"

#include "TmpCamera.h"
#include "Core/Timer.h"

#include "Core/GameState.h"
#include "EngineTestGameState.h"
#include "Core/SleepyEngine.h"