#pragma once

#include "../Event.h"

struct SDL_ControllerAxisEvent;

namespace QUtils::Drawing::SDL
{
	struct ControllerAxisEvent : public Event
	{
		int which;
		unsigned char axis;
		short value;
		
		
		
		
		
		ControllerAxisEvent(const SDL_ControllerAxisEvent*);
		ControllerAxisEvent(const SDL_ControllerAxisEvent&);
	};
}