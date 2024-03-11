// SleepyGame.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SleepyGame.h"
#include "OldSleepyEngine.h"
#include "Core/SleepyEngine.h"
#include "EngineTestGameState.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "Core/GameState.h"
#include "Graphics/Renderer.h"


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
    {
        AllocConsole();
        FILE* consoleOut;
        freopen_s(&consoleOut, "CONOUT$", "w", stdout);

        SleepyEngine engine2;

        RendererDescriptor rendererDescriptor;
        rendererDescriptor.windowWidth = 800;
        rendererDescriptor.windowHeight = 600;
        engine2.Initialize<EngineTestGameState>(hInstance, &rendererDescriptor);
        engine2.Run();

        /*OldSleepyEngine engine(hInstance);
        engine.Initialize();
        engine.Run();*/



        fclose(consoleOut);
        FreeConsole();
    }
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
