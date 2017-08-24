#pragma once

#include "../Event.h"

struct SDL_DollarGestureEvent;

namespace QUtils::Drawing::SDL
{
	struct DollarGestureEvent : public Event
	{
		int touchId;
		int gestureId;
		unsigned int numFingers;
		float error;
		float x;
		float y;
		
		DollarGestureEvent(const SDL_DollarGestureEvent*);
		DollarGestureEvent(const SDL_DollarGestureEvent&);
	};
}