// SleepyGame.cpp : Defines the entry point for the application.
//
#include "pch.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

#ifdef _DEBUG
    _CrtMemState memStateInit;
    _CrtMemCheckpoint(&memStateInit);
#endif

    UNREFERENCED_PARAMETER(hPrevInstance); 
    UNREFERENCED_PARAMETER(lpCmdLine); 

   /* AllocConsole();
    FILE consoleOut;*/

    /*GameApp* pGameApp = GameApp::Instance();
    pGameApp->Initialize();
    pGameApp->Release();*/
    GameFactory* factory = new GameFactory();

    SleepyEngine engine(hInstance);
    engine.SetFactory(factory);
    engine.Initialize();
    engine.Run();


    /*if (&consoleOut != 0)
        fclose(&consoleOut);
    FreeConsole();*/

#ifdef _DEBUG
    _CrtMemState memStateEnd, memStateDiff;
    _CrtMemCheckpoint(&memStateEnd);
    if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
    {
        MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
    }
#endif 
    

    return 0;
}
