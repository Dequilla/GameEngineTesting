#include <iostream>

#include "Window.hpp"

int main(int argc, char** argv)
{
	hs::Window window(1280, 720, L"Hello world!", 1);

	while (true)
	{
		hs::Event e;
		while (window.pollEvents(e))
		{
		}
	}
}