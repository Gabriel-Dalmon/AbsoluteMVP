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
class Utils;
class Camera;
class Component;
class Collider;
class ColliderOBB;
class ColliderSphere;
class Entity;
class Mesh;
class MeshRenderer;
class MeshReference;
class Script;
class Shader;
class OldShader;
class ShaderReference;
class Timer;
class Transform;
class Device;
class SwapChain;
class CommandQueue;
class Window;

struct SystemEntityData;
class System;
struct RendererEntityData;
struct RendererDescriptor;
class Renderer;
class GameState;
class EngineTestGameState;
class SleepyEngine;
class OldSleepyEngine;


// MACROS
#define RELEASE(p) {if (p){ p->Release(); p = nullptr;}}
#define MAX_LOADSTRING 100

// NAMESPACES
using namespace DirectX;

// Classes 
#include "Utils/Utils.h"
#include "UploadBuffer.h"
#include "Utils/HResultException.h"
#include "Utils/Constants.h"
using namespace Sleepy;

#include "ECS/Component.h"
#include "Components/Transform.h"
#include "Components/MeshReference.h"
#include "Components/ShaderReference.h"
#include "Collider.h"
#include "ColliderOBB.h"
#include "ColliderSphere.h"
#include "MeshRenderer.h"
#include "Script.h"

#include "ECS/Entity.h"

#include "PSO.h"

#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Graphics/CommandQueue.h"
#include "Graphics/Window.h"
#include "Graphics/Shader.h"

#include "Mesh.h"


#include "ECS/System.h"
#include "Graphics/Renderer.h"


#include "Camera.h"

#include "OldShader.h"

#include "Timer.h"

#include "tmpMeshGeo.h"
#include "Core/GameState.h"
#include "EngineTestGameState.h"
#include "Core/SleepyEngine.h"
#include "OldSleepyEngine.h"
