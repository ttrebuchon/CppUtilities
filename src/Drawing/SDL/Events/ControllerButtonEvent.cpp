#include <QUtils/Drawing/SDL/Events/ControllerButtonEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	ControllerButtonEvent::ControllerButtonEvent(const SDL_ControllerButtonEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(which);
		INIT_MEMBER(button);
		INIT_MEMBER(state);
	}
	
	ControllerButtonEvent::ControllerButtonEvent(const SDL_ControllerButtonEvent& ev) : ControllerButtonEvent(&ev)
	{}
	
	#else
	
	#endif
}