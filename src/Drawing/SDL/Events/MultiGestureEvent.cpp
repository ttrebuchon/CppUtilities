#include <QUtils/Drawing/SDL/Events/MultiGestureEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	MultiGestureEvent::MultiGestureEvent(const SDL_MultiGestureEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(touchId);
		INIT_MEMBER(dTheta);
		INIT_MEMBER(dDist);
		INIT_MEMBER(x);
		INIT_MEMBER(y);
		INIT_MEMBER(numFingers);
	}
	
	MultiGestureEvent::MultiGestureEvent(const SDL_MultiGestureEvent& ev) : MultiGestureEvent(&ev)
	{}
	
	#else
	
	#endif
}