#pragma once

class Device;

class CommandQueue
{
public:
	CommandQueue();
	~CommandQueue();

	int Initialize(Device* pDevice);
	void Execute();
	void Signal();
	void Flush();
	int CleanUp();



private:
	ID3D12CommandQueue* m_pD3DCommandQueue = nullptr;
};