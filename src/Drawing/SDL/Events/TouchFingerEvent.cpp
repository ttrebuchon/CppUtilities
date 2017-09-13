#include <QUtils/Drawing/SDL/Events/TouchFingerEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	TouchFingerEvent::TouchFingerEvent(const SDL_TouchFingerEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(touchId);
		INIT_MEMBER(fingerId);
		INIT_MEMBER(x);
		INIT_MEMBER(y);
		INIT_MEMBER(dx);
		INIT_MEMBER(dy);
		INIT_MEMBER(pressure);
	}
	
	TouchFingerEvent::TouchFingerEvent(const SDL_TouchFingerEvent& ev) : TouchFingerEvent(&ev)
	{}
	
	#else
	
	#endif
}