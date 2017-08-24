#pragma once

#include "../Event.h"

struct SDL_JoyButtonEvent;

namespace QUtils::Drawing::SDL
{
	struct JoyButtonEvent : public Event
	{
		int which;
		unsigned char button;
		unsigned char state;
		
		
		
		JoyButtonEvent(const SDL_JoyButtonEvent*);
		JoyButtonEvent(const SDL_JoyButtonEvent&);
	};
}