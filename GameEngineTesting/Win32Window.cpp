#include "Win32Window.hpp"
#include "windowsx.h"

hs::priv::Win32Window::Win32Window(uint32 width, uint32 height, String title, uint32 style)
{
	// Retrieves the application base process handle
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
		MessageBox(NULL,
			"Call to CreateWindowExW failed! (window)",
			"Hillside error",
			MB_ICONERROR
		);
	}

	// Window visibility
	if (style & Style::WINDOW_SHOW)
	{
		ShowWindow(m_windowHandle, SW_SHOW);
	}
	else if (style & Style::WINDOW_HIDE)
	{
		ShowWindow(m_windowHandle, SW_HIDE);
	}
	
	// Window type
	if (style & Style::WINDOW_FULLSCREEN)
		this->switchToFullscreen(width, height);

	// Keep track of all our windows
	m_windowsCreated.emplace(m_windowHandle, this);
}

hs::priv::Win32Window::~Win32Window()
{
	// This window is being deleted, remove from our tracked windows.
	hs::priv::Win32Window::m_windowsCreated.erase(m_windowHandle);
}

void hs::priv::Win32Window::setPosition(uint32 x, uint32 y)
{
	// TODO
}

void hs::priv::Win32Window::setSize(uint32 width, uint32 height)
{
	// TODO
}

void hs::priv::Win32Window::setTitle(String title)
{
	// TODO
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

// Properly declare and define static variable
std::unordered_map<HWND, hs::priv::Win32Window*> hs::priv::Win32Window::m_windowsCreated;

hs::priv::Win32Window* hs::priv::Win32Window::getWindowFromhandle(HWND winHandle)
{
	try
	{
		return hs::priv::Win32Window::m_windowsCreated.at(winHandle);
	}
	catch(const std::out_of_range& exc)
	{
		return nullptr;
	}

	return nullptr;
}

void hs::priv::Win32Window::switchToFullscreen(uint32 width, uint32 height)
{
	DEVMODEW devMode;
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth = width;
	devMode.dmPelsHeight = height;
	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	if (ChangeDisplaySettingsW(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		MessageBox(NULL,
			"ChangeDisplaySettingsW failed! (window)",
			"Hillside error",
			MB_ICONERROR
		);
		return;
	}

	// Make the window flags compatible with fullscreen mode
	SetWindowLongW(m_windowHandle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	SetWindowLongW(m_windowHandle, GWL_EXSTYLE, WS_EX_APPWINDOW);

	// Resize the window so that it fits the entire screen
	SetWindowPos(m_windowHandle, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED);
	ShowWindow(m_windowHandle, SW_SHOW);
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
		MessageBox(NULL,
			"Call to RegisterClassEx failed! (window)",
			"Hillside error",
			MB_ICONERROR
		);

		return false;
	}

	return true;
}

void hs::priv::Win32Window::processEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	// TODO: https://docs.microsoft.com/sv-se/windows/desktop/winmsg/about-messages-and-message-queues
	// https://docs.microsoft.com/sv-se/windows/desktop/inputdev/wm-keydown
	// https://docs.microsoft.com/sv-se/windows/desktop/inputdev/wm-keyup
	// https://docs.microsoft.com/sv-se/windows/desktop/inputdev/mouse-input-notifications
	// TODO: WM_SIZING

	hs::Event e;
	switch (msg)
	{
	case WM_KEYDOWN:
		// Translate key
		break;

	case WM_KEYUP:
		// Translate key
		break;

	case WM_MOUSEMOVE:
		break;
	
	case WM_MOUSEWHEEL:
		break;
	
	case WM_LBUTTONUP:
		e.type = Event::MouseReleased;
		e.mouseButton.code = Event::MouseButton::LEFT;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_MBUTTONUP:
		e.type = Event::MouseReleased;
		e.mouseButton.code = Event::MouseButton::MIDDLE;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_RBUTTONUP:
		e.type = Event::MouseReleased;
		e.mouseButton.code = Event::MouseButton::RIGHT;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_XBUTTONUP:
		e.type = Event::MouseReleased;
		if(GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			e.mouseButton.code = Event::MouseButton::EXTRA1;
		else
			e.mouseButton.code = Event::MouseButton::EXTRA2;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_LBUTTONDOWN:
		e.type = Event::MousePressed;
		e.mouseButton.code = Event::MouseButton::LEFT;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_MBUTTONDOWN:
		e.type = Event::MousePressed;
		e.mouseButton.code = Event::MouseButton::MIDDLE;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_RBUTTONDOWN:
		e.type = Event::MousePressed;
		e.mouseButton.code = Event::MouseButton::RIGHT;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_XBUTTONDOWN:
		e.type = Event::MousePressed;
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			e.mouseButton.code = Event::MouseButton::EXTRA1;
		else
			e.mouseButton.code = Event::MouseButton::EXTRA2;
		e.mouseButton.ctrl = (wParam & MK_CONTROL);
		e.mouseButton.shift = (wParam & MK_SHIFT);
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_CLOSE:
		e.type = hs::Event::Close;
		this->pushEvent(e);
		break;
	}
}

LRESULT CALLBACK hs::priv::Win32Window::WndProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Warning: Do not keep this pointer around. It will be deleted when the window is.
	hs::priv::Win32Window* window = hs::priv::Win32Window::getWindowFromhandle(handle);

	if (window != nullptr)
	{
		window->processEvent(msg, wParam, lParam);
	}

	// We don't want the OS to close our window, we do that
	if (msg == WM_CLOSE)
		return 0;

	return DefWindowProcW(handle, msg, wParam, lParam);
}
