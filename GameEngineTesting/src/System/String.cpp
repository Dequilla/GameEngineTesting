#include "String.hpp"

hs::String::String(std::wstring string)
	: m_string (string) {}

hs::String::String(const String& string)
	: m_string(string.m_string) {}

hs::String::String(const wchar_t* string)
	: m_string(string) {}

hs::String& hs::String::operator=(const std::wstring& right)
{
	this->m_string = right;
	return *this;
}

hs::String& hs::String::operator=(const String& right)
{
	m_string = right.m_string;
	return *this;
}

hs::String& hs::String::operator=(const wchar_t* right)
{
	m_string = std::wstring(right);
	return *this;
}

std::wstring hs::String::getString()
{
	return m_string;
}

const wchar_t* hs::String::getCString()
{
	return m_string.c_str();
}
