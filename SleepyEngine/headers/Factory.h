#pragma once

class Factory 
{
public:
	Factory();
	~Factory();
	void Init(RessourceAllocator* rRessourceAllocator);
	void SetSignatureAndPSO(SleepyEngine* pEngine);

	void FillPlayer(Entity* pEntity);

protected:
	RessourceAllocator* m_pRessourceAllocator;
	ID3D12PipelineState* m_PSOTexture = nullptr;
	ID3D12PipelineState* m_PSOColor = nullptr;
	ID3D12RootSignature* m_pRootSignatureTexture = nullptr;
	ID3D12RootSignature* m_pRootSignatureColor = nullptr;
};