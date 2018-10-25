#include <iostream>

#include "Window.hpp"

////////////////////////////////////////////
//
//	DONT FORGET
//	 - Switch to the right dev-branch
//	 - Commit stable code
//
//	TODO
//	 - Implement styles for Win32Window
//	 - Finish events for Win32Window
//	 - Implement built-in profiling
//	 - Implement WindowHandle
//	 - Create a message and error system
//	 - Implement capture mouse to window
//
//	CURRENT KNOWN ISSUES
//	 - None (Except that it isn't finished)
//
////////////////////////////////////////////

const hs::uint32 WIDTH = 1280;
const hs::uint32 HEIGHT = 720;

int main(int argc, char** argv)
{
	hs::Window window(WIDTH, HEIGHT, L"Hello world!", hs::Window::Style::WINDOW_SHOW);
	
	while (window.isOpen())
	{
		hs::Event e;
		while (window.pollEvents(e))
		{
			if (e.type == hs::Event::Close)
				window.close();
		}
	}
}