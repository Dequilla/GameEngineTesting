#include "Win32Window.hpp"

#include "../Keyboard.hpp"

#include "windowsx.h"

#include <cstdlib>

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
	DestroyWindow(m_windowHandle);
}

void hs::priv::Win32Window::setPosition(uint32 x, uint32 y)
{
	SetWindowPos(m_windowHandle, HWND_TOP, x, y, getWidth(), getHeight(), SWP_FRAMECHANGED);
}

void hs::priv::Win32Window::setSize(uint32 width, uint32 height)
{
	SetWindowPos(m_windowHandle, HWND_TOP, getPosX(), getPosY(), width, height, SWP_FRAMECHANGED);
}

void hs::priv::Win32Window::setTitle(String title)
{
	SetWindowTextW(m_windowHandle, title.getCString());
}

hs::uint32 hs::priv::Win32Window::getWidth()
{
	RECT rect;
	if (GetWindowRect(m_windowHandle, &rect))
		return std::abs(rect.right - rect.left);
	else
		return 0;
}

hs::uint32 hs::priv::Win32Window::getHeight()
{
	RECT rect;
	if (GetWindowRect(m_windowHandle, &rect))
		return std::abs(rect.bottom - rect.top);
	else
		return 0;
}

hs::int32 hs::priv::Win32Window::getPosX()
{
	RECT rect;
	if (GetWindowRect(m_windowHandle, &rect))
		return rect.left;
	else
		return 0;
}

hs::int32 hs::priv::Win32Window::getPosY()
{
	RECT rect;
	if (GetWindowRect(m_windowHandle, &rect))
		return rect.top;
	else
		return 0;
}

hs::WindowHandle hs::priv::Win32Window::getSystemHandle()
{
	return WindowHandle(m_windowHandle);
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

hs::priv::Win32Window* hs::priv::Win32Window::getWindowFromHandle(HWND winHandle)
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

// Properly declare and define static variable
bool hs::priv::Win32Window::m_windowClassRegistered = false;

bool hs::priv::Win32Window::registerWindowClass()
{
	// Only register once
	if (!m_windowClassRegistered)
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

		m_windowClassRegistered = true;
	}

	return true;
}

void hs::priv::Win32Window::processEvent(UINT msg, WPARAM wParam, LPARAM lParam)
{
	hs::Event e;
	switch (msg)
	{
	case WM_SIZE:
		e.type = Event::Resized;
		e.size.width = LOWORD(lParam);
		e.size.height = HIWORD(lParam);
		this->pushEvent(e);
		break;

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		e.type = Event::KeyPressed;
		e.key.code = this->translateVirtualKeycode(wParam, lParam);

		e.key.control = HIWORD(GetKeyState(VK_CONTROL));
		e.key.shift = HIWORD(GetKeyState(VK_SHIFT));
		e.key.alt = HIWORD(GetKeyState(VK_MENU));
		e.key.system = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));

		this->pushEvent(e);
		break;

	case WM_SYSKEYUP:
	case WM_KEYUP:
		e.type = Event::KeyReleased;
		e.key.code = this->translateVirtualKeycode(wParam, lParam);

		e.key.control = HIWORD(GetKeyState(VK_CONTROL));
		e.key.shift = HIWORD(GetKeyState(VK_SHIFT));
		e.key.alt = HIWORD(GetKeyState(VK_MENU));
		e.key.system = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));

		this->pushEvent(e);
		break;

	case WM_MOUSEMOVE:
		e.type = Event::MouseMoved;
		e.mouseMove.x = GET_X_LPARAM(lParam);
		e.mouseMove.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;
	
	case WM_MOUSEWHEEL:
		e.type = Event::MouseWheel;
		e.mouseWheel.x = GET_X_LPARAM(lParam);
		e.mouseWheel.y = GET_Y_LPARAM(lParam);
		e.mouseWheel.delta = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		this->pushEvent(e);
		break;
	
	case WM_LBUTTONUP:
		e.type = Event::MouseReleased;
		e.mouseButton.code = Event::MouseButton::LEFT;
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_MBUTTONUP:
		e.type = Event::MouseReleased;
		e.mouseButton.code = Event::MouseButton::MIDDLE;
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_RBUTTONUP:
		e.type = Event::MouseReleased;
		e.mouseButton.code = Event::MouseButton::RIGHT;
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
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_LBUTTONDOWN:
		e.type = Event::MousePressed;
		e.mouseButton.code = Event::MouseButton::LEFT;
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_MBUTTONDOWN:
		e.type = Event::MousePressed;
		e.mouseButton.code = Event::MouseButton::MIDDLE;
		e.mouseButton.x = GET_X_LPARAM(lParam);
		e.mouseButton.y = GET_Y_LPARAM(lParam);
		this->pushEvent(e);
		break;

	case WM_RBUTTONDOWN:
		e.type = Event::MousePressed;
		e.mouseButton.code = Event::MouseButton::RIGHT;
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
	hs::priv::Win32Window* window = hs::priv::Win32Window::getWindowFromHandle(handle);

	if (window != nullptr)
	{
		window->processEvent(msg, wParam, lParam);
	}

	// We don't want the OS to close our window, we do that
	if (msg == WM_CLOSE)
		return 0;

	return DefWindowProcW(handle, msg, wParam, lParam);
}

hs::Keyboard::Key hs::priv::Win32Window::translateVirtualKeycode(WPARAM key, LPARAM lParam)
{
	switch (key)
	{
	
	case VK_SHIFT:
	{
		UINT leftShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);

		// Bit 16-23 is the scancode of this key event(will get lshift or rshift here)
		// Then translate the bits back to the start so it can be compared to VK_LSHIFT
		UINT scancode = static_cast<UINT>((lParam & 0x00ff0000) >> 16);
		return (scancode == leftShift ? Keyboard::LShift : Keyboard::RShift);
	}

	// Check the "extended" flag to distinguish between left and right alt
	case VK_MENU: return (HIWORD(lParam) & KF_EXTENDED) ? Keyboard::RAlt : Keyboard::LAlt;

	// Check the "extended" flag to distinguish between left and right control
	case VK_CONTROL: return (HIWORD(lParam) & KF_EXTENDED) ? Keyboard::RControl : Keyboard::LControl;

	case 'A': return Keyboard::A;
	case 'B': return Keyboard::B;
	case 'C': return Keyboard::C;
	case 'D': return Keyboard::D;
	case 'E': return Keyboard::E;
	case 'F': return Keyboard::F;
	case 'G': return Keyboard::G;
	case 'H': return Keyboard::H;
	case 'I': return Keyboard::I;
	case 'J': return Keyboard::J;
	case 'K': return Keyboard::K;
	case 'L': return Keyboard::L;
	case 'M': return Keyboard::M;
	case 'N': return Keyboard::N;
	case 'O': return Keyboard::O;
	case 'P': return Keyboard::P;
	case 'Q': return Keyboard::Q;
	case 'R': return Keyboard::R;
	case 'S': return Keyboard::S;
	case 'T': return Keyboard::T;
	case 'U': return Keyboard::U;
	case 'V': return Keyboard::V;
	case 'X': return Keyboard::X;
	case 'Y': return Keyboard::Y;
	case 'Z': return Keyboard::Z;
	case '0': return Keyboard::Num0;
	case '1': return Keyboard::Num1;
	case '2': return Keyboard::Num2;
	case '3': return Keyboard::Num3;
	case '4': return Keyboard::Num4;
	case '5': return Keyboard::Num5;
	case '6': return Keyboard::Num6;
	case '7': return Keyboard::Num7;
	case '8': return Keyboard::Num8;
	case '9': return Keyboard::Num9;

	case VK_NUMPAD0: return Keyboard::Numpad1;
	case VK_NUMPAD1: return Keyboard::Numpad2;
	case VK_NUMPAD2: return Keyboard::Numpad3;
	case VK_NUMPAD3: return Keyboard::Numpad4;
	case VK_NUMPAD4: return Keyboard::Numpad5;
	case VK_NUMPAD5: return Keyboard::Numpad6;
	case VK_NUMPAD6: return Keyboard::Numpad7;
	case VK_NUMPAD7: return Keyboard::Numpad8;
	case VK_NUMPAD8: return Keyboard::Numpad9;
	case VK_NUMPAD9: return Keyboard::Numpad0;

	case VK_F1: return Keyboard::F1;
	case VK_F2: return Keyboard::F2;
	case VK_F3: return Keyboard::F3;
	case VK_F4: return Keyboard::F4;
	case VK_F5: return Keyboard::F5;
	case VK_F6: return Keyboard::F6;
	case VK_F7: return Keyboard::F7;
	case VK_F8: return Keyboard::F8;
	case VK_F9: return Keyboard::F9;
	case VK_F10: return Keyboard::F10;
	case VK_F11: return Keyboard::F11;
	case VK_F12: return Keyboard::F12;
	case VK_F13: return Keyboard::F13;
	case VK_F14: return Keyboard::F14;
	case VK_F15: return Keyboard::F15;

	case VK_LEFT: return Keyboard::Left;
	case VK_RIGHT: return Keyboard::Right;
	case VK_UP: return Keyboard::Up;
	case VK_DOWN: return Keyboard::Down;
	
	case VK_LWIN: return Keyboard::LSystem;
	case VK_RWIN: return Keyboard::RSystem;
	
	case VK_APPS: return Keyboard::Menu;
	case VK_OEM_1: return Keyboard::Semicolon;
	case VK_OEM_2: return Keyboard::Slash;
	case VK_OEM_PLUS: return Keyboard::Equal;
	case VK_OEM_MINUS: return Keyboard::Hyphen;
	case VK_OEM_4: return Keyboard::LBracket;
	case VK_OEM_6: return Keyboard::RBracket;
	case VK_OEM_COMMA: return Keyboard::Comma;
	case VK_OEM_PERIOD: return Keyboard::Period;
	case VK_OEM_7: return Keyboard::Quote;
	case VK_OEM_5: return Keyboard::Backslash;
	case VK_OEM_3: return Keyboard::Tilde;
	case VK_ESCAPE: return Keyboard::Escape;
	case VK_SPACE: return Keyboard::Space;
	case VK_RETURN: return Keyboard::Enter;
	case VK_BACK: return Keyboard::Backspace;
	case VK_TAB: return Keyboard::Tab;
	case VK_PRIOR: return Keyboard::PageUp;
	case VK_NEXT: return Keyboard::PageDown;
	case VK_END: return Keyboard::End;
	case VK_HOME: return Keyboard::Home;
	case VK_INSERT: return Keyboard::Insert;
	case VK_DELETE: return Keyboard::Delete;
	case VK_ADD: return Keyboard::Add;
	case VK_SUBTRACT: return Keyboard::Subtract;
	case VK_MULTIPLY: return Keyboard::Multiply;
	case VK_DIVIDE: return Keyboard::Divide;
	case VK_PAUSE: return Keyboard::Pause;
	
	}

	return Keyboard::Unknown;
}
