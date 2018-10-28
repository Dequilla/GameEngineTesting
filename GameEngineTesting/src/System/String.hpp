#pragma once
#include <string>

#include "Types.hpp"

namespace hs
{

	class String
	{
		std::wstring m_string;

	public:
		String(std::wstring string);
		String(const String& string);
		String(const wchar_t* string);

		String& operator=(const std::wstring& right);
		String& operator=(const String& right);
		String& operator=(const wchar_t* right);

		std::wstring getString();
		const wchar_t* getCString();
	};

}