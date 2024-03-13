// SleepyGame.cpp : Defines the entry point for the application.
//

#include "pch.h"

#include "SleepyGame.h"
#include "Thread.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>


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

    AllocConsole();
    FILE consoleOut;
    
    Thread game(hInstance, &consoleOut);

#ifdef _DEBUG
    _CrtMemState memStateEnd, memStateDiff;
    _CrtMemCheckpoint(&memStateEnd);
    if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
    {
        MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
    }
#endif 

    while (true) {};

    if (&consoleOut != 0)
        fclose(&consoleOut);
    FreeConsole();

    return 0;
}