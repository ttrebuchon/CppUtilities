#include <QUtils/Drawing/SDL/Events/JoyHatEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	JoyHatEvent::JoyHatEvent(const SDL_JoyHatEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	JoyHatEvent::JoyHatEvent(const SDL_JoyHatEvent& ev) : JoyHatEvent(&ev)
	{}
	
	#else
	
	#endif
}