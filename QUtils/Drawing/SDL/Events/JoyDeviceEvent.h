#pragma once

#include "../Event.h"

struct SDL_JoyDeviceEvent;

namespace QUtils::Drawing::SDL
{
	struct JoyDeviceEvent : public Event
	{
		int which;
		
		
		
		
		
		JoyDeviceEvent(const SDL_JoyDeviceEvent*);
		JoyDeviceEvent(const SDL_JoyDeviceEvent&);
	};
}