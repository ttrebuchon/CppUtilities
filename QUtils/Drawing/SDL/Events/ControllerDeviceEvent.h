#pragma once

#include "../Event.h"

struct SDL_ControllerDeviceEvent;

namespace QUtils::Drawing::SDL
{
	struct ControllerDeviceEvent : public Event
	{
		int which;
		
		
		
		
		
		ControllerDeviceEvent(const SDL_ControllerDeviceEvent*);
		ControllerDeviceEvent(const SDL_ControllerDeviceEvent&);
	};
}