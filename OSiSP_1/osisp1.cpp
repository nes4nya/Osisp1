#include <Windows.h>
#include <tchar.h>

int x = 100;
int y = 10;
int checkFig = 1;
int checkUP = 0;
int x_end = 500; 
int y_end = 500;
HWND HMainWindow;

void DrawRectangle(HWND hWnd, int x, int y, int check) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(hdc, hbrush);
	if (check==1)
		Rectangle(hdc, x, y, x + 70, y + 50);
	else 
		Ellipse(hdc, x, y, x + 70, y + 50);
	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, 
	HINSTANCE Prev, 
	LPTSTR cmd, 
	int mode) 
{
	HWND hWnd; 
	MSG msg; 
	WNDCLASS wc; 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 
	wc.lpfnWndProc = WndProc; 
	wc.style = CS_HREDRAW | CS_VREDRAW; 
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION); 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.lpszMenuName = NULL; 
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; 
 
	hWnd = CreateWindow(WinName, 
		_T("Sprite"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		500, 
		500, 
		HWND_DESKTOP, 
		NULL, 
		This, 
		NULL); 
	ShowWindow(hWnd, mode); 
	HMainWindow = hWnd;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		x_end = LOWORD(lParam);
		y_end = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		checkFig = -checkFig;
		InvalidateRect(HMainWindow, 0, TRUE);
		UpdateWindow(HMainWindow);
		DrawRectangle(HMainWindow, x, y, checkFig);
		break;
	case WM_KEYUP:
		checkUP = 0;
		break;
	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) > 0 && !(wParam & MK_SHIFT)) {
			if (y > 0)
				y -= 2;
			else
				y += 2;
			DrawRectangle(HMainWindow, x, y, checkFig);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		else if ((short)HIWORD(wParam) < 0 && !(wParam & MK_SHIFT)){
			if (y + 50 < y_end)
				y += 2;
			else
				y -= 2;
			DrawRectangle(HMainWindow, x, y, checkFig);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		if ((short)HIWORD(wParam) > 0 && wParam & MK_SHIFT) {
			if (x > 0)
				x -= 2;
			else
				x += 2;
			DrawRectangle(HMainWindow, x, y, checkFig);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		else if ((short)HIWORD(wParam) < 0 && wParam & MK_SHIFT) {
			if (x + 70 < x_end)
				x += 2;
			else
				x -= 2;
			DrawRectangle(HMainWindow, x, y, checkFig);
			InvalidateRect(HMainWindow, 0, TRUE);
			UpdateWindow(HMainWindow);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			if (checkUP) {
				y += 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {
				
				y -= 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (y <= 0){
					checkUP = 1;
				}
			}
		}
		if (wParam == VK_DOWN) {
			if (checkUP) {
				y -= 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {
				y += 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (y + 50 > y_end) {
					checkUP = 1;
				}
			}
		}
		if (wParam == VK_LEFT) {
			if (checkUP) {
				x += 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {

				x -= 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (x <= 0) {
					checkUP = 1;
				}
			}
		}
		if (wParam == VK_RIGHT) {
			if (checkUP) {
				x -= 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
			}
			else {
				x += 2;
				DrawRectangle(HMainWindow, x, y, checkFig);
				InvalidateRect(HMainWindow, 0, TRUE);
				UpdateWindow(HMainWindow);
				if (x + 70 > x_end) {
					checkUP = 1;
				}
			}
		}
		break;
	case WM_PAINT:
		DrawRectangle(HMainWindow, x, y, checkFig);
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break; 
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}