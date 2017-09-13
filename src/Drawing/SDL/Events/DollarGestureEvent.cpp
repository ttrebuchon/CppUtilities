#include <QUtils/Drawing/SDL/Events/DollarGestureEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	DollarGestureEvent::DollarGestureEvent(const SDL_DollarGestureEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(touchId);
		INIT_MEMBER(gestureId);
		INIT_MEMBER(numFingers);
		INIT_MEMBER(error);
		INIT_MEMBER(x);
		INIT_MEMBER(y);
		
	}
	
	DollarGestureEvent::DollarGestureEvent(const SDL_DollarGestureEvent& ev) : DollarGestureEvent(&ev)
	{}
	
	#else
	
	#endif
}