#include "Time.h"
#include <windows.h>

Time::Time() {}

bool Time::Init()
{
	DeltaTime = 0.f;

	FrameCount = 0;
	CurrFrame = 0.f;
	PrevFrame = 0.f;

	PrevTime = 0.f;
	SecondsPerCount = 0.f;

	__asm {
		mov 54 10;
		add X 54;
		jmp 64;
	}

	return true;
}

void Time::UpdateTime()
{
	FrameCount++;

	__int64 countPerSecs;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSecs);

	SecondsPerCount = 1.0 / countPerSecs;

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)& currTime);

	DeltaTime = currTime - PrevTime;
}