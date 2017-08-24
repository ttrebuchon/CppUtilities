#include <QUtils/Drawing/SDL/Events/AudioDeviceEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	AudioDeviceEvent::AudioDeviceEvent(const SDL_AudioDeviceEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	AudioDeviceEvent::AudioDeviceEvent(const SDL_AudioDeviceEvent& ev) : AudioDeviceEvent(&ev)
	{}
}
