#pragma once

#include "../Event.h"
#include "../KeySym.h"

struct SDL_KeyboardEvent;

namespace QUtils::Drawing::SDL
{
	struct KeyboardEvent : public Event
	{
		int windowID;
		unsigned char state;
		unsigned char repeat;
		KeySym keysym;
		
		
		KeyboardEvent(const SDL_KeyboardEvent*);
		KeyboardEvent(const SDL_KeyboardEvent&);
	};
}