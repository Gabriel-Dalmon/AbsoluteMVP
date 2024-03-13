#include "pch.h"
#include "thread.h"
#include "GameFactory.h"


std::vector<HANDLE> Thread::threadList = {};

Thread::Thread(HINSTANCE hInstance, FILE* consoleOut)
{
    m_hInstance = hInstance;
    m_pConsoleOut = consoleOut;
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
    OutputDebugStringA("ca marche\n");
    // demander a Sylvain pourquoi il accepte printf et cerr mais pas cout 
    freopen_s(&m_pConsoleOut, "CONOUT$", "w", stdout);
    freopen_s(&m_pConsoleOut, "CONOUT$", "w", stderr);
    SleepyEngine engine(m_hInstance);

    std::cout << "we summoned!" << std::endl;
    std::cerr << "we err!" << std::endl;

    GameFactory* factory = new GameFactory;
    engine.SetFactory(factory);
    engine.Initialize();
    engine.Run();
    
    engine.Release();
}