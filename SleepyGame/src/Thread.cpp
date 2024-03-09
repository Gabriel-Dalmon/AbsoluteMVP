#include "pch.h"
#include "thread.h"


std::vector<HANDLE> Thread::threadList = {};

Thread::Thread(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread::SummonThread, (void*)this, 0, NULL);
}

Thread::~Thread() {

}

void Thread::SummonThread(void* Instance)
{
    std::cout << "we summoned!" << std::endl;
    Thread* This = (Thread*)Instance;
    This->m_This = (HANDLE)Instance;
    threadList.push_back(This->m_This);
    This->RunThread();
}

void Thread::RunThread()
{
    SleepyEngine engine(m_hInstance);
    engine.Initialize();
    engine.Run();
}