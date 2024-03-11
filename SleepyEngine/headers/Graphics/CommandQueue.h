#pragma once

class Device;

class CommandQueue
{
public:
	CommandQueue();
	~CommandQueue();

	int Initialize(Device* pDevice);
	void Execute(unsigned int commandsListsCount, ID3D12CommandList* const commandsLists[]);
	void Signal();
	void Flush();
	int Release();



private:
	ID3D12CommandQueue* m_pD3DCommandQueue = nullptr;
};