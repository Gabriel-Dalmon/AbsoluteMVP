#pragma once

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
	FILE* m_pConsoleOut = nullptr;
};