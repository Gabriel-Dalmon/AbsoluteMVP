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
class Collider;
class ColliderOBB;
class ColliderSphere;
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
#define MAX_LOADSTRING 100
#define SWAP_CHAIN_BUFFER_COUNT 2

// NAMESPACES
using namespace DirectX;

// STRUCTS
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

// Classes 
#include "ComponentDescriptor.h"
#include "Camera.h"
#include "Component.h"
#include "Collider.h"
#include "ColliderOBB.h"
#include "ColliderSphere.h"
#include "Entity.h"
#include "GameState.h"
#include "Input.h"
#include "Menu.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Pause.h"
#include "Script.h"
#include "Shader.h"
#include "ShaderReference.h"
#include "Timer.h"
#include "Transform.h"
#include "RessourceAllocator.h"
#include "Factory.h"
#include "tmpMeshGeo.h"
#include "UploadBuffer.h"
#include "PSO.h"
#include "MathHelper.h"
#include "SleepyEngine.h"

