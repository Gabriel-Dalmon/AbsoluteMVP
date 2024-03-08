#include "pch.h"

//TotalTime: temps en s depuis lancement du jeu : float
//DeltaTime: temps écoulé entre deux frames: float

//timeGetTime: en ms

Timer::Timer() {}

bool Timer::Init()
{
	StartTime = timeGetTime();
	DeltaTime = 0.f;
	TotalTime = 0.f;

	currTime = 0.f;
	prevTime = 0.f;

	FrameCount = 0;
	FPSTimer = 0.f;
	MaxFPS = 0;

	std::cout << timeGetTime() << std::endl;

	return true;
}

float Timer::GetTotalTime()
{
	return (timeGetTime() - StartTime)*0.001;
}

float Timer::GetDeltaTime()
{
	return DeltaTime;
}

void Timer::UpdateTimer()
{
	currTime = GetTotalTime();

	DeltaTime = currTime - prevTime;

	prevTime = currTime;
}

void Timer::UpdateFPS(HWND Window)
{
	FrameCount += 1;
	if ((GetTotalTime() - FPSTimer) >= 1.f)
	{
		std::wstring title = L"FPS: " + std::to_wstring(FrameCount) + L" | Max FPS: " + std::to_wstring(MaxFPS);

		if (FrameCount > MaxFPS)
			MaxFPS = FrameCount;

		FrameCount = 0;
		FPSTimer += GetTotalTime() - FPSTimer;
		
		// Might be temporary, might not be
		// Depends on if we can figure out "fonts"
		SetWindowText(Window, title.c_str());
	}
}