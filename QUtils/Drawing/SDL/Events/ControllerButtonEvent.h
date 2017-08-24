#pragma once

#include "../Event.h"

struct SDL_ControllerButtonEvent;

namespace QUtils::Drawing::SDL
{
	struct ControllerButtonEvent : public Event
	{
		int which;
		unsigned char button;
		unsigned char state;
		
		
		
		
		ControllerButtonEvent(const SDL_ControllerButtonEvent*);
		ControllerButtonEvent(const SDL_ControllerButtonEvent&);
	};
}