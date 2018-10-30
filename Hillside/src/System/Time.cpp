#include "Time.hpp"

hs::Time::Time(float seconds)
{
	m_microseconds = static_cast<int64>(seconds * 1000000);
}

hs::Time::Time(int32 milliseconds)
{
	m_microseconds = static_cast<int64>(milliseconds * 1000);
}

hs::Time::Time(int64 microseconds)
	: m_microseconds(microseconds)
{
}

float hs::Time::asSeconds()
{
	return m_microseconds / 1000000;
}

hs::int32 hs::Time::asMilliseconds()
{
	return m_microseconds / 1000;
}

hs::int64 hs::Time::asMicroseconds()
{
	return m_microseconds;
}
