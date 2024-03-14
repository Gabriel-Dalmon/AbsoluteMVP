#pragma once

class GameApp
{
public:
	~GameApp() {};

	// INIT
	void Initialize(); 

	// Setter / Getter
	static GameApp* Instance();

	// Engine linked functions
	void Draw();

	// RELEASE
	void Release();

private:
	// SINGLETON
	GameApp() {};
	ThreadApp* m_pThreadApp = nullptr;
};

