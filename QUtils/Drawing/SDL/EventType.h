#pragma once
#include "Version.h"
#include <string>

namespace QUtils::Drawing::SDL
{
	enum struct EventType : unsigned int
	{
		FirstEvent,
		Quit,
		App_Terminating,
		App_LowMemory,
		App_WillEnterBackground,
		App_DidEnterBackground,
		App_WillEnterForeground,
		App_DidEnterForeground,
		WindowEvent,
		SysWMEvent,
		KeyDown,
		KeyUp,
		TextEditing,
		TextInput,
		KeymapChanged,
		MouseMotion,
		MouseButtonDown,
		MouseButtonUp,
		MouseWheel,
		JoyAxisMotion,
		JoyBallMotion,
		JoyHatMotion,
		JoyButtonDown,
		JoyButtonUp,
		JoyDeviceAdded,
		JoyDeviceRemoved,
		ControllerAxisMotion,
		ControllerButtonDown,
		ControllerButtonUp,
		ControllerDeviceAdded,
		ControllerDeviceRemoved,
		ControllerDeviceRemapped,
		FingerDown,
		FingerUp,
		FingerMotion,
		DollarGesture,
		DollarRecord,
		MultiGesture,
		ClipboardUpdate,
		DropFile,
		#if SDL_VERSION_MIN(2, 0, 5)
		DropText,
		DropBegin,
		DropComplete,
		#endif
		AudioDeviceAdded,
		AudioDeviceRemoved,
		Render_Targets_Reset,
		Render_Device_Reset,
		UserEvent,
		LastEvent
	};
	
	unsigned int SDL_RawEventType(EventType);
	EventType SDL_EnumEventType(unsigned int);
	std::string SDL_EventTypeName(EventType);
	inline std::string SDL_EventTypeName(unsigned int type)
	{
		return SDL_EventTypeName(SDL_EnumEventType(type));
	}
	
	
}