#pragma once
#include "../Event.h"

struct SDL_MouseButtonEvent;

namespace QUtils::Drawing::SDL
{
	struct MouseButtonEvent : public Event
	{
		unsigned int windowID;
		unsigned int which;
		unsigned char button;
		unsigned char state;
		unsigned char clicks;
		int x;
		int y;
		
		MouseButtonEvent(const SDL_MouseButtonEvent*);
		MouseButtonEvent(const SDL_MouseButtonEvent&);
		
	};
}