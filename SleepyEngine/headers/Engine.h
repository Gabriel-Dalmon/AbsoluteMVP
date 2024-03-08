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
#include "d3dx12.h"
#include "MathHelper.h"

// FORWARD DECLARATIONS
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
class SleepyEngine;
class Timer;
class Transform;

// MACROS
#define RELEASE(p) {if (p){ p->Release(); p = nullptr;}}
#define MAX_LOADSTRING 100
#define SWAP_CHAIN_BUFFER_COUNT 2

// NAMESPACES
using namespace DirectX;

// Classes 
#include "Camera.h"
#include "ECS/Component.h"
#include "Collider.h"
#include "ColliderOBB.h"
#include "ColliderSphere.h"
#include "ECS/Entity.h"
#include "Core/GameState.h"
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
#include "UploadBuffer.h"
#include "Utils/HResultException.h"
#include "PSO.h"
#include "tmpMeshGeo.h"
#include "OldSleepyEngine.h"