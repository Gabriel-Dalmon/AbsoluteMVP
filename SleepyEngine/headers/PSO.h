#pragma once

#include <d3d12.h>
#include <d3dx12.h>


typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODescriptor;

PSODescriptor InitPSO();

void DeletePSO(PSODescriptor* pso);