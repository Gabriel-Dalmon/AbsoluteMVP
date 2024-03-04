#pragma once

#ifndef _WINDEF_
class HINSTANCE__; // Forward or never
typedef HINSTANCE__* HINSTANCE;
#endif
typedef WORD ATOM;

class Window
{
public:
	Window();
	~Window();

	int Initialize(HINSTANCE hInstance, int windowWidth, int windowHeight);
	ATOM RegisterWindowClass();
	void CleanUp(); 

	inline HWND GetWindowHandle() const { return m_hWnd; };
	inline int GetWindowWidth() const { return m_windowWidth; };
	inline int GetWindowHeight() const { return m_windowHeight; };

	static LRESULT __stdcall WindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hWnd = nullptr;
	HINSTANCE m_hAppInstance = nullptr;
	int m_windowWidth = 0;
	int m_windowHeight = 0;
};