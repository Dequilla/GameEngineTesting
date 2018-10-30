#include <iostream>

#include <Window/Window.hpp>
#include <Window/Keyboard.hpp>

////////////////////////////////////////////
//
//	DONT FORGET
//	 - Switch to the right dev-branch
//	 - Commit stable code
//
//	TODO
//	 - Implement built-in profiling
//	 - Create a message and error system
//	 - Implement capture mouse to window
//	 - Possible make a include folder and keep all header files in there and cpp files only in the src folder
//	 - Keyboard no repeat
//	 - Create OpenGL/rendering context
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

			if (e.type == hs::Event::KeyPressed)
			{
				if (e.key.code == hs::Keyboard::A)
				{
					window.setSize(320, 160);
					window.setPosition(1337, 200);
					window.setTitle(L"NEW");
				}
			}
			if (e.type == hs::Event::KeyReleased)
			{
				if (e.key.code == hs::Keyboard::A)
				{
					window.setSize(WIDTH, HEIGHT);
					window.setPosition(0, 0);
					window.setTitle(L"Hello world!");
				}
			}
		}
	}

	return 0;
}