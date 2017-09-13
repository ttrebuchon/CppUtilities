#include <QUtils/Drawing/SDL/Events/MouseButtonEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	MouseButtonEvent::MouseButtonEvent(const SDL_MouseButtonEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(windowID);
		INIT_MEMBER(which);
		INIT_MEMBER(button);
		INIT_MEMBER(state);
		INIT_MEMBER(clicks);
		INIT_MEMBER(x);
		INIT_MEMBER(y);
	}
	
	MouseButtonEvent::MouseButtonEvent(const SDL_MouseButtonEvent& ev) : MouseButtonEvent(&ev)
	{}
	
	#else
	
	#endif
}