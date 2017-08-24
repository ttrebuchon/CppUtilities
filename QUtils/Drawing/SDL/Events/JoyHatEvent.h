#pragma once

#include "../Event.h"

struct SDL_JoyHatEvent;

namespace QUtils::Drawing::SDL
{
	struct JoyHatEvent : public Event
	{
		int which;
		unsigned char hat;
		unsigned char value;
		
		
		
		JoyHatEvent(const SDL_JoyHatEvent*);
		JoyHatEvent(const SDL_JoyHatEvent&);
	};
}