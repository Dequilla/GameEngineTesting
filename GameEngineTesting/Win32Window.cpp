#include "Win32Window.hpp"

hs::priv::Win32Window::Win32Window(uint32 width, uint32 height, String title, uint32 style)
{
	m_systemHandle = GetModuleHandle(nullptr);

	bool isRegistered = this->registerWindowClass();
	
	m_windowHandle = CreateWindowExW(
		NULL,
		this->className,
		title.getCString(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		m_systemHandle,
		NULL
	);

	if (!m_windowHandle)
	{
		// TODO: Create a message and error system
		MessageBox(NULL,
			"Call to CreateWindowExW failed! (window)",
			"Hillside error",
			MB_ICONERROR
		);
	}

	this->setVisible(true);
}

hs::priv::Win32Window::~Win32Window()
{
}

void hs::priv::Win32Window::setPosition(uint32 x, uint32 y)
{
}

void hs::priv::Win32Window::setSize(uint32 width, uint32 height)
{
}

void hs::priv::Win32Window::setTitle(String title)
{
}

void hs::priv::Win32Window::setStyle(uint32 style)
{
}

void hs::priv::Win32Window::setVisible(bool visibile)
{
	if (false)
		ShowWindow(m_windowHandle, SW_HIDE);
	else
		ShowWindow(m_windowHandle, SW_SHOW);

	UpdateWindow(m_windowHandle);
}

hs::WindowHandle hs::priv::Win32Window::getSystemHandle()
{
	return WindowHandle();
}

void hs::priv::Win32Window::processEvents()
{
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

bool hs::priv::Win32Window::registerWindowClass()
{
	WNDCLASSEXW windowClassExW;

	windowClassExW.cbSize = sizeof(WNDCLASSEXW);
	windowClassExW.style = CS_HREDRAW | CS_VREDRAW;
	windowClassExW.lpfnWndProc = this->WndProc;
	windowClassExW.cbClsExtra = 0;
	windowClassExW.cbWndExtra = 0;
	windowClassExW.hInstance = m_systemHandle;
	windowClassExW.hIcon = LoadIcon(m_systemHandle, MAKEINTRESOURCE(IDI_APPLICATION));
	windowClassExW.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClassExW.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClassExW.lpszMenuName = NULL;
	windowClassExW.lpszClassName = this->className;
	windowClassExW.hIconSm = LoadIcon(m_systemHandle, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassExW(&windowClassExW))
	{
		// TODO: Create a message and error system
		MessageBox(NULL,
			"Call to RegisterClassEx failed! (window)",
			"Hillside error",
			MB_ICONERROR
		);

		return false;
	}

	return true;
}

LRESULT CALLBACK hs::priv::Win32Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE)
		return 0; // We want to handle closing the window to not leak and lose resources

	return DefWindowProcW(handle, message, wParam, lParam);
}
