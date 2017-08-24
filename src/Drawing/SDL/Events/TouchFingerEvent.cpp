#include <QUtils/Drawing/SDL/Events/TouchFingerEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	TouchFingerEvent::TouchFingerEvent(const SDL_TouchFingerEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	TouchFingerEvent::TouchFingerEvent(const SDL_TouchFingerEvent& ev) : TouchFingerEvent(&ev)
	{}
}
