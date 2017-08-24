#include <QUtils/Drawing/SDL/EventType.h>
#include "IfSDL.h"
#include <map>


namespace QUtils::Drawing::SDL
{
	namespace Helpers
	{
		std::map<SDL_EventType, EventType> reverseMap(const std::map<EventType, SDL_EventType>& map)
		{
			std::map<SDL_EventType, EventType> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFTYPE(x, y) { EventType::x, SDL_##y, }
	
	static std::map<EventType, SDL_EventType> types = {
		DEFTYPE(FirstEvent, FIRSTEVENT),
		DEFTYPE(Quit, QUIT),
		DEFTYPE(App_Terminating, APP_TERMINATING),
		DEFTYPE(App_LowMemory, APP_LOWMEMORY),
		DEFTYPE(App_WillEnterBackground, APP_WILLENTERBACKGROUND),
		DEFTYPE(App_DidEnterBackground, APP_DIDENTERBACKGROUND),
		DEFTYPE(App_WillEnterForeground, APP_WILLENTERFOREGROUND),
		DEFTYPE(App_DidEnterForeground, APP_DIDENTERFOREGROUND),
		DEFTYPE(WindowEvent, WINDOWEVENT),
		DEFTYPE(SysWMEvent, SYSWMEVENT),
		DEFTYPE(KeyDown, KEYDOWN),
		DEFTYPE(KeyUp, KEYUP),
		DEFTYPE(TextEditing, TEXTEDITING),
		DEFTYPE(TextInput, TEXTINPUT),
		DEFTYPE(KeymapChanged, KEYMAPCHANGED),
		DEFTYPE(MouseMotion, MOUSEMOTION),
		DEFTYPE(MouseButtonDown, MOUSEBUTTONDOWN),
		DEFTYPE(MouseButtonUp, MOUSEBUTTONUP),
		DEFTYPE(MouseWheel, MOUSEWHEEL),
		DEFTYPE(JoyAxisMotion, JOYAXISMOTION),
		DEFTYPE(JoyBallMotion, JOYBALLMOTION),
		DEFTYPE(JoyHatMotion, JOYHATMOTION),
		DEFTYPE(JoyButtonDown, JOYBUTTONDOWN),
		DEFTYPE(JoyButtonUp, JOYBUTTONUP),
		DEFTYPE(JoyDeviceAdded, JOYDEVICEADDED),
		DEFTYPE(JoyDeviceRemoved, JOYDEVICEREMOVED),
		DEFTYPE(ControllerAxisMotion, CONTROLLERAXISMOTION),
		DEFTYPE(ControllerButtonDown, CONTROLLERBUTTONDOWN),
		DEFTYPE(ControllerButtonUp, CONTROLLERBUTTONUP),
		DEFTYPE(ControllerDeviceAdded, CONTROLLERDEVICEADDED),
		DEFTYPE(ControllerDeviceRemoved, CONTROLLERDEVICEREMOVED),
		DEFTYPE(ControllerDeviceRemapped, CONTROLLERDEVICEREMAPPED),
		DEFTYPE(FingerDown, FINGERDOWN),
		DEFTYPE(FingerUp, FINGERUP),
		DEFTYPE(FingerMotion, FINGERMOTION),
		DEFTYPE(DollarGesture, DOLLARGESTURE),
		DEFTYPE(DollarRecord, DOLLARRECORD),
		DEFTYPE(MultiGesture, MULTIGESTURE),
		DEFTYPE(ClipboardUpdate, CLIPBOARDUPDATE),
		DEFTYPE(DropFile, DROPFILE),
		#ifdef SDL_2_0_5
		DEFTYPE(DropText, DROPTEXT),
		DEFTYPE(DropBegin, DROPBEGIN),
		DEFTYPE(DropComplete, DROPCOMPLETE),
		#endif
		DEFTYPE(AudioDeviceAdded, AUDIODEVICEADDED),
		DEFTYPE(AudioDeviceRemoved, AUDIODEVICEREMOVED),
		DEFTYPE(Render_Targets_Reset, RENDER_TARGETS_RESET),
		DEFTYPE(Render_Device_Reset, RENDER_DEVICE_RESET),
		DEFTYPE(UserEvent, USEREVENT),
		DEFTYPE(LastEvent, LASTEVENT),
	};
	
	static std::map<SDL_EventType, EventType> revTypes = Helpers::reverseMap(types);
	
	
	
	int SDL_RawEventType(EventType type)
	{
		return types.at(type);
	}
	
	EventType SDL_EnumEventType(int type)
	{
		return revTypes.at((SDL_EventType)type);
	}
}