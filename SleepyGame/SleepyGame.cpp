// SleepyGame.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SleepyGame.h"
#include "SleepyEngine.h"
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


    //https://stackoverflow.com/questions/191842/how-do-i-get-console-output-in-c-with-a-windows-program
    HWND consoleWindowHandle = GetConsoleWindow();
    if (consoleWindowHandle == nullptr)
    {
        AllocConsole();
        CONSOLE_SCREEN_BUFFER_INFO coninfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
        coninfo.dwSize.Y = 500;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

        HANDLE hSTDOut = GetStdHandle(STD_OUTPUT_HANDLE);
        int hConHandle = _open_osfhandle((long)hSTDOut, _O_TEXT);
        FILE* fp = _fdopen(hConHandle, "w");
        setvbuf(fp, NULL, _IONBF, 0);
        std::cout << "Console Enabled";
        std::ios::sync_with_stdio();
    }
    else
    {
        ShowWindow(consoleWindowHandle, SW_SHOW);
        std::cout << "Message 2";
    }


    SleepyEngine engine(hInstance);
    engine.Initialize();
    engine.Run();

    return 0;
}
