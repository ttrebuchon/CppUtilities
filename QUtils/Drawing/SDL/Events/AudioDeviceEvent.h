#pragma once

#include "../Event.h"

struct SDL_AudioDeviceEvent;

namespace QUtils::Drawing::SDL
{
	struct AudioDeviceEvent : public Event
	{
		unsigned int which;
		unsigned char iscapture;
		
		
		
		
		
		AudioDeviceEvent(const SDL_AudioDeviceEvent*);
		AudioDeviceEvent(const SDL_AudioDeviceEvent&);
	};
}