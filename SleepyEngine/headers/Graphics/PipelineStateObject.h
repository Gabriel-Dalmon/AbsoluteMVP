#pragma once

class PipelineStateObject
{
public:
	PipelineStateObject();
	~PipelineStateObject();

	int Initialize();
	int BuildShaders();
	int Release();
};