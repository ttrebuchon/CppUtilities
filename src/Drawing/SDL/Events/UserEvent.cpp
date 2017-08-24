#include <QUtils/Drawing/SDL/Events/UserEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	UserEvent::UserEvent(const SDL_UserEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	UserEvent::UserEvent(const SDL_UserEvent& ev) : UserEvent(&ev)
	{}
}
