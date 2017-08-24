#pragma once

#include "../Event.h"

struct SDL_JoyBallEvent;

namespace QUtils::Drawing::SDL
{
	struct JoyBallEvent : public Event
	{
		int which;
		unsigned char ball;
		short xrel;
		short yrel;
		
		
		
		JoyBallEvent(const SDL_JoyBallEvent*);
		JoyBallEvent(const SDL_JoyBallEvent&);
	};
}