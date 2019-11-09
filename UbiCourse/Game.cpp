#include <windows.h>

bool Running = true;

LRESULT CALLBACK Win32MainWindowCallback(HWND Window, UINT msg, WPARAM wParam, LPARAM lParam) {
	LRESULT Result = 0;
	switch (msg)
	{
	case WM_CLOSE: 
		Running = false;
		break;
	case WM_DESTROY:

		Running = false;
		break;
	case WM_PAINT:
		break;
	default:
		Result = DefWindowProc(Window, msg, wParam, lParam);
		break;
	}
	return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {

	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS WindowClass = {};

	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = "MainWindowClass";

	RegisterClass(&WindowClass);

	//Creating a window

	int WindowX = 500;
	int WindowY = 10;
	int WindowWidth = 800;
	int WindowHeight = 450;

	HWND Window = CreateWindowEx(
		0,
		WindowClass.lpszClassName,
		"Main Game Window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		WindowX,
		WindowY,
		WindowWidth,
		WindowHeight,
		NULL, NULL, hInstance, NULL);


	ShowWindow(Window, nCmdShow);

	//The Message Loop
	
		MSG msg;
		while (Running && PeekMessage(&msg, 0, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	
	return 0;
}