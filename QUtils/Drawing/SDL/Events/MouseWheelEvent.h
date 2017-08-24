#pragma once

#include "../Event.h"

struct SDL_MouseWheelEvent;

namespace QUtils::Drawing::SDL
{
	struct MouseWheelEvent : public Event
	{
		unsigned int windowID;
		unsigned int which;
		int x;
		int y;
		unsigned int direction;
		
		MouseWheelEvent(const SDL_MouseWheelEvent*);
		MouseWheelEvent(const SDL_MouseWheelEvent&);
	};
}