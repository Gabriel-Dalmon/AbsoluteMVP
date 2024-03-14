#pragma once

class Thread
{
public:
	Thread() {};
	~Thread() {};

	// Init
	void Initialize();

	virtual void OnThread(HINSTANCE hInstance) {};


protected:
	HINSTANCE hInstance;
	HANDLE m_hThread; 
	DWORD m_ThreadId; 
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
};