#include <QUtils/Drawing/SDL/Events/DropEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	DropEvent::DropEvent(const SDL_DropEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	DropEvent::DropEvent(const SDL_DropEvent& ev) : DropEvent(&ev)
	{}
}
