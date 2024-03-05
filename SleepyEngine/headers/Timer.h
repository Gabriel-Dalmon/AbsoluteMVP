#pragma once

class Timer
{
	public:
		Timer();
		bool Init();

		void UpdateTimer();
		void UpdateFPS(HWND Window);

		float GetTotalTime();
		float GetDeltaTime();

	private:

		float StartTime;

		float DeltaTime;
		float TotalTime;

		float currTime;
		float prevTime;

		float FPSTimer;
		int FrameCount;
		int MaxFPS;
};