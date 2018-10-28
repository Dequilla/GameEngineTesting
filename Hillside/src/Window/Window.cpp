#include "Window.hpp"

hs::Window::Window(uint32 width, uint32 height, String title, uint32 style)
{
	create(width, height, title, style);
}

hs::Window::~Window()
{
	close();
}

void hs::Window::create(uint32 width, uint32 height, String title, uint32 style)
{
	// Close any previous window
	close(); 

	m_implementation = hs::priv::WindowImpl::create(width, height, title, style);
}

void hs::Window::close()
{
	delete m_implementation;
	m_implementation = nullptr;
}

bool hs::Window::isOpen()
{
	return (m_implementation != nullptr);
}

bool hs::Window::pollEvents(Event& e)
{
	if(this->m_implementation != nullptr)
		return m_implementation->popEvent(e);
	return false;
}

void hs::Window::setPosition(uint32 x, uint32 y)
{
	m_implementation->setPosition(x, y);
}

void hs::Window::setSize(uint32 width, uint32 height)
{
	m_implementation->setSize(width, height);
}

void hs::Window::setTitle(String title)
{
	m_implementation->setTitle(title);
}

hs::uint32 hs::Window::getWidth()
{
	return m_implementation->getWidth();
}

hs::uint32 hs::Window::getHeight()
{
	return m_implementation->getHeight();
}

hs::int32 hs::Window::getPosX()
{
	return m_implementation->getPosX();
}

hs::int32 hs::Window::getPosY()
{
	return m_implementation->getPosY();
}
