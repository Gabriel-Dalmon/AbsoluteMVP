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
class CustomScript;

class Entity;

class Window;
class Device;
class SwapChain;
class CommandQueue;
class FrameResource;
class Shader;

class Timer;
class Camera;

struct SystemEntityData;
class System;

struct RendererEntityData;
struct RendererDescriptor;
class Renderer;

class GameState;
class EngineTestGameState;

class SleepyEngine;


// MACROS
#define RELEASE(p) {if (p){ p->Release(); p = nullptr;}}
#define MAX_LOADSTRING 100


// NAMESPACES
using namespace DirectX;

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

#include "ECS/Component.h"
#include "Components/Transform.h"
#include "Components/MeshReference.h"
#include "Components/ShaderReference.h"
#include "Components/Collider.h"
#include "Components/ColliderOBB.h"
#include "Components/ColliderSphere.h"
#include "Components/CustomScript.h"

#include "ECS/Entity.h"

#include "Graphics/Window.h"
#include "Graphics/Device.h"
#include "Graphics/SwapChain.h"
#include "Graphics/FrameResource.h"
#include "Graphics/CommandQueue.h"
#include "Graphics/Shader.h"

#include "Mesh.h"


#include "ECS/System.h"
#include "Graphics/Renderer.h"


#include "Camera.h"
#include "Core/Timer.h"

#include "Core/GameState.h"
#include "EngineTestGameState.h"
#include "Core/SleepyEngine.h"