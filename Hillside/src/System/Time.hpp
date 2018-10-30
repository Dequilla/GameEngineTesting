#pragma once
#include "../Config.hpp"

namespace hs
{
	
	class HILLSIDE_API Time
	{
	public:
		Time(float seconds);
		Time(int32 milliseconds);
		Time(int64 microseconds);

		float asSeconds();
		int32 asMilliseconds();
		int64 asMicroseconds();

	private:
		int64 m_microseconds;
	};

}