#include <QUtils/Drawing/SDL/Events/DropEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	DropEvent::DropEvent(const SDL_DropEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(file);
		#if SDL_VERSION_MIN(2,0,5)
		INIT_MEMBER(windowID);
		#endif
	}
	
	DropEvent::DropEvent(const SDL_DropEvent& ev) : DropEvent(&ev)
	{}
	
	#else
	
	#endif
}