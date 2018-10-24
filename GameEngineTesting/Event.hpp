#pragma once

namespace hs
{

	struct Event
	{
	public:
		struct KeyEvent
		{

		};

		struct MouseMoveEvent
		{
		
		};

		enum EventType
		{
			KeyPressed,
			KeyReleased,
			MouseMoved,

			Count // Keep last -- Number of available event types
		};

		union
		{
			KeyEvent key;
			MouseMoveEvent mouseMove;
		};
	};

}