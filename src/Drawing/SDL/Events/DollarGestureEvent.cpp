#include <QUtils/Drawing/SDL/Events/DollarGestureEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	DollarGestureEvent::DollarGestureEvent(const SDL_DollarGestureEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	DollarGestureEvent::DollarGestureEvent(const SDL_DollarGestureEvent& ev) : DollarGestureEvent(&ev)
	{}
}
