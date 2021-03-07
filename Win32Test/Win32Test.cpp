#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
#define OPEN_FILE_BUTTON 5
#define SAVE_FILE_BUTTON 6
#define IDM_FILE_NEW 7
#define IDM_FILE_OPEN 8
#define IDM_FILE_QUIT 9

#pragma warning(disable : 4996)

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void LoadImages();
void RegisterDialogClass(HINSTANCE);
void DisplayDialog(HWND);
void OpenFile(HWND);
void DisplayFile(char*);

HMENU hMenu;
HWND hName, hAge, hOut, hLogo, hMainWindow, hEdit;
HBITMAP hLogoImage, hGenerateImage;

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

	RegisterDialogClass(hInstance);

	hMainWindow = CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 900, 500, NULL, NULL, NULL, NULL);

	// MessageBoxW(NULL, L"Hello World", L"My GUI", MB_OK);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void DisplayFile(char* path)
{
	FILE* file;
	file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	int _size = ftell(file);
	rewind(file);
	char* data = new char[_size + 1];
	fread(data, _size, 1, file);
	data[_size] = '\0';

	SetWindowText(hEdit, data);

	fclose(file);
}

void WriteFile(char* path)
{
	FILE* file;
	file = fopen(path, "w");

	int _size = GetWindowTextLength(hEdit);

	char* data = new char[_size + 1];
	GetWindowText(hEdit, data, _size);

	fwrite(data, _size + 1, 1, file);

	fclose(file);
}

void OpenFile(HWND hWnd)
{
	OPENFILENAME ofn;

	char file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "All files\0*.*\0SourceFiles\0*.CPP\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;

	GetOpenFileName(&ofn);

	DisplayFile(ofn.lpstrFile);

	//MessageBox(NULL, ofn.lpstrFile, "", MB_OK);
}

void SaveFile(HWND hWnd)
{
	OPENFILENAME ofn;

	char file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "All files\0*.*\0SourceFiles\0*.CPP\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;

	GetSaveFileName(&ofn);

	WriteFile(ofn.lpstrFile);

	//MessageBox(NULL, ofn.lpstrFile, "", MB_OK);
}

// WM_CHAR : Khi nhập 1 kí tự từ bàn phím
// WM_COMMAND:Khi lựa chọn các item trong popup menu
// WM_CREATE : Khi windows được tạo
// WM_DESTROY : Khi windows bị destroy
// WM_LBUTTONDOWN : Khi click chuột trái
// WM_RBUTTONDOWN : Khi click chuột phải
// WM_MOUSEMOVE : Khi di chuyển con trỏ chuột
// WM_PAINT : Khi windows được vẽ lại
// WM_QUIT : Khi close windows


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");
	int val;
	POINT point;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (wp)
		{
		case IDM_FILE_NEW:
		case IDM_FILE_OPEN:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case IDM_FILE_QUIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case OPEN_FILE_BUTTON:
			OpenFile(hWnd);
			break;
		case SAVE_FILE_BUTTON:
			SaveFile(hWnd);
			break;
		case FILE_MENU_EXIT:
			// MB_ABORTRETRYIGNORE, MB_CANCELTRYCONTINUE, MB_HELP
			// MB_OK, MB_OKCANCEL, MB_RETRYCANCEL, MB_YESNO, MB_YESNOCANCEL
			// MB_ICONEXCLAMATION, MB_ICONWARNING, MB_ICONINFORMATION, MB_ICONASTERISK
			// MB_ICONQUESTION, MB_ICONSTOP, MB_ICONERROR, MB_ICONHAND
			// IDABORT 3, IDCANCEL 2, IDCONTINUE 11, IDIGNORE 5, IDNO 7, IDOK 1, IDRETRY 4, IDTRYAGAIN 10, IDYES 6
			val = MessageBoxW(hWnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);
			if (val == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else if (val == IDNO)
			{

			}
			break;
		case FILE_MENU_NEW:
			DisplayDialog(hWnd);
			MessageBeep(MB_ICONINFORMATION);
			break;
		case GENERATE_BUTTON:
			char name[30], age[10], out[50];
			GetWindowText(hName, name, 30);
			GetWindowText(hAge, age, 10);

			if (strcmp(name, "") == 0 || strcmp(age, "") == 0)
			{
				val = MessageBoxW(hWnd, L"You did not enter anything!", NULL, MB_ICONERROR | MB_ICONEXCLAMATION | MB_ABORTRETRYIGNORE);
				switch (val)
				{
				case IDABORT:
					DestroyWindow(hWnd);
					break;
				case IDRETRY:
					return 0;
				case IDIGNORE:
					break;
				}
			}

			strcpy(out, name);
			strcat(out, " is ");
			strcat(out, age);
			strcat(out, " years old.");

			SetWindowText(hOut, out);

			break;

		}
		break;
	case WM_RBUTTONUP:
		point.x = LOWORD(lp);
		point.y = HIWORD(lp);
		hMenu = CreatePopupMenu();
		ClientToScreen(hWnd, &point);

		AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, TEXT("&New"));
		AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, TEXT("&Open"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, IDM_FILE_QUIT, TEXT("&Quit"));

		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hWnd, NULL);
		DestroyMenu(hMenu);
		break;
	case WM_CREATE:
		LoadImages();
		AddMenus(hWnd);
		AddControls(hWnd);
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

void AddControls(HWND hWnd)
{
	CreateWindowW(L"Static", L"Name:", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
	hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Static", L"Age:", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
	hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Generate", WS_VISIBLE | WS_CHILD, 150, 140, 98, 38, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);

	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
	hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);

	CreateWindowW(L"Button", L"Open File", WS_VISIBLE | WS_CHILD, 450, 10, 150, 36, hWnd, (HMENU)OPEN_FILE_BUTTON, NULL, NULL);
	CreateWindowW(L"Button", L"Save File", WS_VISIBLE | WS_CHILD, 600, 10, 150, 36, hWnd, (HMENU)SAVE_FILE_BUTTON, NULL, NULL);

	hEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
		450, 50, 400, 300, hWnd, NULL, NULL, NULL);
}

void LoadImages()
{
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"C:\\Users\\nhatv\\Work\\DialogBase\\Win32Test\\Logo.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
}

LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case 1:
			EnableWindow(hMainWindow, true);
			DestroyWindow(hWnd);
			break;
		}
	case WM_CLOSE:
		EnableWindow(hMainWindow, true);
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void RegisterDialogClass(HINSTANCE hInstance)
{
	WNDCLASSW dialog = { 0 };

	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_CROSS);
	dialog.hInstance = hInstance;
	dialog.lpszClassName = L"myDialogClass";
	dialog.lpfnWndProc = DialogProcedure;

	RegisterClassW(&dialog);
}

void DisplayDialog(HWND hWnd)
{
	HWND hDlg = CreateWindowW(L"myDialogClass", L"Dialog", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 200, 200, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Close", WS_VISIBLE | WS_CHILD, 20, 20, 100, 40, hDlg, (HMENU)1, NULL, NULL);

	EnableWindow(hWnd, false);
}