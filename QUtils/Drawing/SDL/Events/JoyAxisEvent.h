#pragma once

#include "../Event.h"

struct SDL_JoyAxisEvent;

namespace QUtils::Drawing::SDL
{
	struct JoyAxisEvent : public Event
	{
		int which;
		unsigned char axis;
		short value;
		
		
		
		JoyAxisEvent(const SDL_JoyAxisEvent*);
		JoyAxisEvent(const SDL_JoyAxisEvent&);
	};
}