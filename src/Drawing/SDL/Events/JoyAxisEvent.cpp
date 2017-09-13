#include <QUtils/Drawing/SDL/Events/JoyAxisEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	
	JoyAxisEvent::JoyAxisEvent(const SDL_JoyAxisEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	JoyAxisEvent::JoyAxisEvent(const SDL_JoyAxisEvent& ev) : JoyAxisEvent(&ev)
	{}
	
	#else
	
	#endif
}