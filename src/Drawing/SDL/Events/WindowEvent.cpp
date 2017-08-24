#include <QUtils/Drawing/SDL/Events/WindowEvent.h>
#include "../IfSDL.h"
#include <QUtils/Drawing/SDL/WindowEventType.h>

namespace QUtils::Drawing::SDL
{
	WindowEvent::WindowEvent(const SDL_WindowEvent* ev) : Event(ev->type, ev->timestamp), windowID(ev->windowID), event(SDL_EnumWindowEventType(ev->event)), data1(ev->data1), data2(ev->data2)
	{
		
	}
	
	WindowEvent::WindowEvent(const SDL_WindowEvent& ev) : WindowEvent(&ev)
	{
		
	}
}