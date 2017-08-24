#pragma once

#include "../Event.h"

struct SDL_TouchFingerEvent;

namespace QUtils::Drawing::SDL
{
	struct Finger;
	
	struct TouchFingerEvent : public Event
	{
		long touchId;
		long fingerId;
		float x;
		float y;
		float dx;
		float dy;
		float pressure;
		
		TouchFingerEvent(const SDL_TouchFingerEvent*);
		TouchFingerEvent(const SDL_TouchFingerEvent&);
		
		Finger* getFinger(int index);
	};
}