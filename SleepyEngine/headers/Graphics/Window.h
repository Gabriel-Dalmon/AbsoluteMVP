#pragma once

typedef void* HINSTANCE;

class Window
{
public:
	Window(HINSTANCE hInstance);
	~Window();

	void Initialize(int m_windowWidth, int m_windowHeight);
	ATOM RegisterWindowClass();
	void CleanUp();

	inline HWND GetWindowHandle() const { return m_hWnd; }
	inline int GetWindowWidth() const { return m_windowWidth; }
	inline int GetWindowHeight() const { return m_windowHeight; }

private:
	HWND m_hWnd = nullptr;
	HINSTANCE m_hAppInstance = nullptr;
	int m_windowWidth = 0;
	int m_windowHeight = 0;
};