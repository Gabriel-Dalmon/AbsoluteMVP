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

		float StartTime = 0.0f;

		float DeltaTime = 0.0f;
		float TotalTime = 0.0f;

		float currTime = 0.0f;
		float prevTime = 0.0f;

		float FPSTimer = 0.0f;
		int FrameCount = 0.0f;
		int MaxFPS = 0.0f;
};