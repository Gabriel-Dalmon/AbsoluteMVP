#include "pch.h"

void Thread::Initialize()
{
	m_hThread = CreateThread(NULL, 0, ThreadProc, (void*)this, 0, &m_ThreadId); 
	WaitForSingleObject(m_hThread, INFINITE);
	if (m_hThread == NULL) 
	{
		std::cout << "Error creating the Thread." << std::endl; 
		return;
	}
	std::cout << "Thread created" << std::endl; 
	return;
}
	
DWORD CALLBACK Thread::ThreadProc(LPVOID lpParam)
{
	Thread* pThread = (Thread*)lpParam;
	pThread->OnThread(pThread->hInstance); 

	return 0;
}
