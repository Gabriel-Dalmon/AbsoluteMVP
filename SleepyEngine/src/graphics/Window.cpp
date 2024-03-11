#include "pch.h"

Window::Window()
{
}

Window::~Window()
{
}

int Window::Initialize(HINSTANCE hAppInstance, RendererDescriptor* rendererDescriptor)
{
    m_hAppInstance = hAppInstance;
    m_windowWidth = rendererDescriptor->windowWidth;
    m_windowHeight = rendererDescriptor->windowHeight;
    RegisterWindowClass(rendererDescriptor);

    m_hWnd = CreateWindow(
        rendererDescriptor->hAppClassName, 
        rendererDescriptor->hAppTitle, 
        WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        m_windowWidth, 
        m_windowHeight, 
        0, 
        0, 
        m_hAppInstance, 
        0
    );

    if (m_hWnd == NULL)
    {
        MessageBox(0, L"CreateWindow FAILED", 0, 0);
        return -1;
    }

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    return 0;
}

ATOM Window::RegisterWindowClass(RendererDescriptor* rendererDescriptor)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hAppInstance;
    wcex.hIcon = rendererDescriptor->hAppIcon == nullptr ? LoadIcon(m_hAppInstance, MAKEINTRESOURCE(IDI_SLEEPYENGINE)) : rendererDescriptor->hAppIcon;
    wcex.hCursor = rendererDescriptor->hAppCursor == nullptr ? LoadCursor(nullptr, IDC_ARROW) : rendererDescriptor->hAppCursor;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SLEEPYENGINE);
    wcex.lpszClassName = rendererDescriptor->hAppClassName;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void Window::Release()
{
    // Close window
}

LRESULT CALLBACK Window::WindowProcess(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
            /*case IDM_ABOUT:
                DialogBox((HINSTANCE)wParam, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;*/
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
