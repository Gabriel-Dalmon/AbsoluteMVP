#pragma once

class Time
{
	public:
		Time();
		bool Init();

		void UpdateTime();

	private:

		float DeltaTime;

		int FrameCount;
		float CurrFrame;
		float PrevFrame;

		float SecondsPerCount;
		float PrevTime;
};