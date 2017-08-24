#pragma once

#include "../Event.h"

struct SDL_MouseMotionEvent;

namespace QUtils::Drawing::SDL
{
	struct MouseMotionEvent : public Event
	{
		unsigned int windowID;
		unsigned int which;
		unsigned int state;
		int x;
		int y;
		int xrel;
		int yrel;
		
		MouseMotionEvent(const SDL_MouseMotionEvent*);
		MouseMotionEvent(const SDL_MouseMotionEvent&);
	};
}