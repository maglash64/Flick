#include <windows.h>

//screen width and height
#define	SCRW	GetSystemMetrics(SM_CXSCREEN)
#define	SCRH	GetSystemMetrics(SM_CYSCREEN)
//windiw width and height
#define	WNDW	(0.5*SCRW)
#define WNDH	(0.35*SCRH)
//hotkey IDs
#define HK_TOGGLE_VIEW		900
#define HK_SWIPE_LEFT		901
#define	HK_SWIPE_RIGHT		902
#define	HK_SWIPE_TOP		903
#define	HK_SWIPE_BOTTOM		904
#define	HK_SWITCH_LEFT		905
#define	HK_SWITCH_RIGHT		906

int	isWindowVisible = false;

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND activeWindow = 0;
	switch (msg)
	{
	case WM_HOTKEY:
	{
		if (wParam == HK_TOGGLE_VIEW)
		{
			if (isWindowVisible)
			{
				isWindowVisible = false;
				ShowWindow(hwnd, SW_HIDE);
			}
			else
			{
				ShowWindow(hwnd, SW_SHOW);
				isWindowVisible = true;
			}
		}
		if (wParam == HK_SWIPE_LEFT)
		{
			activeWindow = GetForegroundWindow();
			MoveWindow(activeWindow, 0, 0, SCRW/2, SCRH, 1);
		}
		if (wParam == HK_SWIPE_RIGHT)
		{
			activeWindow = GetForegroundWindow();
			MoveWindow(activeWindow, SCRW/2, 0, SCRW/2, SCRH, 1);
		}
		if (wParam == HK_SWIPE_TOP)
		{
			activeWindow = GetForegroundWindow();
			MoveWindow(activeWindow, 0, 0, SCRW, SCRH/2, 1);
		}
		if (wParam == HK_SWIPE_BOTTOM)
		{
			activeWindow = GetForegroundWindow();
			MoveWindow(activeWindow, 0, SCRH/2, SCRW, SCRH/2, 1);
		}
	}break;
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hin, HINSTANCE hPin, LPWSTR lpcmdline, int nshow)
{
	HWND hwnd;
	MSG	msg;
	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hin;
	wcex.lpfnWndProc = wndProc;
	wcex.lpszClassName = L"Flick";

	if (!RegisterClassEx(&wcex))
	{
		MessageBoxW(0, L"Failed to register window class!", L"Error", MB_OK|MB_ICONERROR);
		return 1;
	}

	if (!(hwnd = CreateWindowW(wcex.lpszClassName, L"Flick", WS_EX_TOPMOST | WS_POPUP, SCRW / 2 - WNDW / 2, SCRH / 2 - WNDH / 2, WNDW, WNDH, HWND_DESKTOP, 0, hin, 0)))
	{
		MessageBoxW(0, L"Failed to create a window!", L"Error", MB_OK|MB_ICONERROR);
	}
	
	RegisterHotKey(hwnd, HK_TOGGLE_VIEW, MOD_CONTROL,VK_ESCAPE);
	RegisterHotKey(hwnd, HK_SWIPE_LEFT, MOD_CONTROL | MOD_ALT, VK_LEFT);
	RegisterHotKey(hwnd, HK_SWIPE_RIGHT, MOD_CONTROL | MOD_ALT, VK_RIGHT);
	RegisterHotKey(hwnd, HK_SWIPE_TOP, MOD_CONTROL | MOD_ALT, VK_UP);
	RegisterHotKey(hwnd, HK_SWIPE_BOTTOM, MOD_CONTROL | MOD_ALT, VK_DOWN);

	while (GetMessage(&msg,0,0,0)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}