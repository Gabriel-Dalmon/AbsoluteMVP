#pragma once

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	void Initialize(IDXGIFactory4*, Device*, Window*);
	void CleanUp();
};