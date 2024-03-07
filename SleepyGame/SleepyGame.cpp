// SleepyGame.cpp : Defines the entry point for the application.
//


#include "SuperHeader.h"
#include "SuperHeader2.h"

#include "framework.h"
#include "SleepyGame.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

void CreateConsoleAndCallEngine(HINSTANCE hInstance)
{
    AllocConsole();
    FILE* consoleOut;
    freopen_s(&consoleOut, "CONOUT$", "w", stdout);
    SleepyEngine engine(hInstance);
    engine.Initialize();

    engine.Run();
   
    if(consoleOut != 0)
        fclose(consoleOut);
    FreeConsole();
}


//int main(int argc, char* argv[])

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
    
    CreateConsoleAndCallEngine(hInstance);

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
