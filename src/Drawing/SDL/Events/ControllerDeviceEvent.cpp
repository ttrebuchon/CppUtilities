#include <QUtils/Drawing/SDL/Events/ControllerDeviceEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	ControllerDeviceEvent::ControllerDeviceEvent(const SDL_ControllerDeviceEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(which);
	}
	
	ControllerDeviceEvent::ControllerDeviceEvent(const SDL_ControllerDeviceEvent& ev) : ControllerDeviceEvent(&ev)
	{}
}