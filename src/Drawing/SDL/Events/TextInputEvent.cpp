#include <QUtils/Drawing/SDL/Events/TextInputEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	TextInputEvent::TextInputEvent(const SDL_TextInputEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(windowID);
		strcpy(this->text, ev->text);
	}
	
	TextInputEvent::TextInputEvent(const SDL_TextInputEvent& ev) : TextInputEvent(&ev)
	{}
}