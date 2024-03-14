#pragma once

class ThreadApp : public Thread
{
public:
	ThreadApp() {};
	~ThreadApp() {};

	void OnThread(HINSTANCE hInstance) override; 

	void Release();
private:
	SleepyEngine* m_pEngine = nullptr;
	GameFactory* m_pFactory = nullptr;
};

