#pragma once

#include <Windows.h>
#include <vector>
#define WIN32_LEAN_AND_MEAN

class Thread
{
public:
	Thread(HINSTANCE hInstance, FILE* consoleOut);
	~Thread();

	static void SummonThread(void* functionAdress);
	static std::vector<HANDLE> threadList;

	void RunThread();


	WSADATA m_wsaData;
	HANDLE m_This;
	HINSTANCE m_hInstance;
	FILE* m_pConsoleOut;
};