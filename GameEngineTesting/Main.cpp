#include <iostream>

#include "Window.hpp"

////////////////////////////////////////////
//
//	DONT FORGET
//	 - Switch to the right dev-branch
//	 - Commit stable code
//
//	CURRENT ISSUES
//	 - Event POP function breaks, for some reason the event queue is popped when empty
//
////////////////////////////////////////////

const hs::uint32 WIDTH = 1280;
const hs::uint32 HEIGHT = 720;

int main(int argc, char** argv)
{
	hs::Window window(WIDTH, HEIGHT, L"Hello world!", 1);

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