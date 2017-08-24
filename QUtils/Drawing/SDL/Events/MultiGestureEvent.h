#pragma once

#include "../Event.h"

struct SDL_MultiGestureEvent;

namespace QUtils::Drawing::SDL
{
	struct MultiGestureEvent : public Event
	{
		/*SDL_TouchID touchId;*/
		float dTheta;
		float dDist;
		float x;
		float y;
		unsigned short numFingers;
		
		MultiGestureEvent(const SDL_MultiGestureEvent*);
		MultiGestureEvent(const SDL_MultiGestureEvent&);
	};
}