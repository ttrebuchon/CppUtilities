#include <QUtils/Drawing/SDL/Events/MouseMotionEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	MouseMotionEvent::MouseMotionEvent(const SDL_MouseMotionEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(windowID);
		INIT_MEMBER(which);
		INIT_MEMBER(state);
		INIT_MEMBER(x);
		INIT_MEMBER(y);
		INIT_MEMBER(xrel);
		INIT_MEMBER(yrel);
	}
	
	MouseMotionEvent::MouseMotionEvent(const SDL_MouseMotionEvent& ev) : MouseMotionEvent(&ev)
	{}
	
	#else
	
	#endif
}