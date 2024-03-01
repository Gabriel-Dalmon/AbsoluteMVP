#pragma once

class Timer
{
	public:
		Timer();
		bool Init();

		void UpdateTimer();

		float GetTotalTime();
		float GetDeltaTime();

	private:

		float StartTime;

		float DeltaTime;
		float TotalTime;

		float currTime;
		float prevTime;
};