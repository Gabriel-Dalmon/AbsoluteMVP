#pragma once

class Window
{
public:
	Window();
	~Window();

	void Initialize(HINSTANCE hInstance, int m_windowWidth, int m_windowHeight);
	void RC();
	void CleanUp();
};