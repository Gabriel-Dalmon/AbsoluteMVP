#pragma once

// LIBS
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

// WINDOWS
#include <Windows.h>
#include <windowsx.h>
#include <wrl.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif

// STD
#include <algorithm>
#include <array>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <fcntl.h>
#include <float.h>
#include <fstream>
#include <iostream>
#include <io.h>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <time.h>
#include <typeinfo>
#include <vector>
#include <unordered_map>

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
#include "d3dx12.h"
#include "MathHelper.h"

// FORWARD DECLARATIONS
class SleepyEngine;
class Camera;
class Component;
class Velocity;
class Collider;
class ColliderOBB;
class ColliderSphere;
class ColliderHandMade;
class Entity;
class GameState;
class Input;
class Menu;
class Mesh;
class MeshRenderer;
class Pause;
class Script;
class Shader;
class ShaderReference;
class Timer;
class Transform;
class Factory;
class RessourceAllocator;

// MACROS
#define RELEASE(p) {if (p){ p->Release(); p = nullptr;}}
#define DELETE(p) {if (p){ delete p; p = nullptr;}}
#define MAX_LOADSTRING 100
#define SWAP_CHAIN_BUFFER_COUNT 2

// NAMESPACES
using namespace DirectX;

// STRUCTS
struct Vertex
{
    Vertex() {}
    Vertex(
        const DirectX::XMFLOAT3& p,
        const DirectX::XMFLOAT3& n,
        const DirectX::XMFLOAT3& t,
        const DirectX::XMFLOAT2& uv) :
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

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT3 TangentU;
    DirectX::XMFLOAT2 TexC;
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

struct ObjectConstants
{
    XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

// Classes 
#include "ComponentDescriptor.h"
#include "Camera.h"
#include "Component.h"
#include "Velocity.h"
#include "Collider.h"
#include "ColliderOBB.h"
#include "ColliderSphere.h"
#include "ColliderHandmade.h"
#include "GameState.h"
#include "Input.h"
#include "Menu.h"
#include "UploadBuffer.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Pause.h"
#include "Script.h"
#include "Shader.h"
#include "Entity.h"
#include "ShaderReference.h"
#include "Timer.h"
#include "Transform.h"
#include "RessourceAllocator.h"
#include "Factory.h"
#include "tmpMeshGeo.h"
#include "PSO.h"
#include "MathHelper.h"
#include "DDSTextureLoader.h"
#include "SleepyEngine.h"

