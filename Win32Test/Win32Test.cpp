#include <windows.h>
#include <tchar.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

HMENU hMenu;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// MessageBox(NULL, _T("Hello World"), _T("My GUI"), MB_OK);
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		}
		break;
	case WM_CREATE:
		AddMenus(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
};

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, _T("SubMenu Item"));

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, _T("New"));
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, _T("Open SubMenu"));
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, _T("Exit"));

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, _T("File"));
	AppendMenu(hMenu, MF_STRING, NULL, _T("Help"));

	SetMenu(hWnd, hMenu);
};