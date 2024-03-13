#pragma once

class Factory
{
public:
	Factory();
	~Factory();

	// Init
	void Initialize(ResourceAllocator* rRessourceAllocator);
	void SetSignatureAndPSO(SleepyEngine* pEngine);

protected:
	ResourceAllocator* m_pRessourceAllocator = nullptr;
	ID3D12PipelineState* m_PSOTexture = nullptr;
	ID3D12PipelineState* m_PSOColor = nullptr;
	ID3D12RootSignature* m_pRootSignatureTexture = nullptr;
	ID3D12RootSignature* m_pRootSignatureColor = nullptr;
};