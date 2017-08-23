#pragma once

namespace QUtils::Drawing::SDL
{
	enum EventType
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
		//DropText,
		//DropBegin,
		//DropComplete,
		AudioDeviceAdded,
		AudioDeviceRemoved,
		Render_Targets_Reset,
		Render_Device_Reset,
		UserEvent,
		LastEvent
	};
	
	int SDL_RawEventType(EventType);
	EventType SDL_EnumEventType(int);
	
	
}