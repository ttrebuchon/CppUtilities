#include <QUtils/Drawing/SDL/Events/UserEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	UserEvent::UserEvent(const SDL_UserEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(windowID);
		INIT_MEMBER(code);
		INIT_MEMBER(data1);
		INIT_MEMBER(data2);
	}
	
	UserEvent::UserEvent(const SDL_UserEvent& ev) : UserEvent(&ev)
	{}
	
	#else
	
	#endif
}