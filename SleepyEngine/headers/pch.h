#pragma once

// FORWARD DECLARATIONS
class Entity;
class Component;
class Mesh;

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
#include "../src/utils/d3dx12.h"



// MACROS
#define RELEASE(p) {if (p){    p->Release();p = nullptr;}}

// NAMESPACES
using namespace DirectX;