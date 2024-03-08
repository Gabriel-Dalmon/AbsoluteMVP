// SleepyGame.cpp : Defines the entry point for the application.
//

#include "SleepyGame.h"
#include "SleepyEngine.h"
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
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    AllocConsole();
    FILE* consoleOut;
    freopen_s(&consoleOut, "CONOUT$", "w", stdout);

    Thread game(hInstance);
    Thread gameTwo(hInstance);

    while (true) {};

    fclose(consoleOut);
    FreeConsole();
    return 0;
}
