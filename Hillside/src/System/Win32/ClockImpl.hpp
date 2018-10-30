#pragma once
#include "../../Config.hpp"
#include "../Time.hpp"

namespace hs
{

	namespace priv
	{

		class HILLSIDE_API ClockImpl
		{
		public:
			static Time getCurrentTime();
		};

	}

}