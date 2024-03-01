#include "pch.h"
#include "Timer.h"

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