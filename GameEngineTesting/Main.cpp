#include "WindowImpl.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	hs::priv::WindowImpl* window = hs::priv::WindowImpl::create(1280, 720, hs::String(L"Hello world!"), 1);

	std::cin.get();

	delete window;
}