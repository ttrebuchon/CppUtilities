#include <QUtils/Drawing/SDL/Events/TextEditingEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	TextEditingEvent::TextEditingEvent(const SDL_TextEditingEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	TextEditingEvent::TextEditingEvent(const SDL_TextEditingEvent& ev) : TextEditingEvent(&ev)
	{}
}
