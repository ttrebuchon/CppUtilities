#include <QUtils/Drawing/SDL/Events/MultiGestureEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	MultiGestureEvent::MultiGestureEvent(const SDL_MultiGestureEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	MultiGestureEvent::MultiGestureEvent(const SDL_MultiGestureEvent& ev) : MultiGestureEvent(&ev)
	{}
}
