#include <QUtils/Drawing/SDL/EventType.h>
#include "IfSDL.h"
#include <map>

#ifdef DEBUG
#include <iostream>
#endif


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	
	namespace Helpers
	{
		std::map<SDL_EventType, EventType> reverseMap(const std::map<EventType, std::tuple<SDL_EventType, std::string>>& map)
		{
			std::map<SDL_EventType, EventType> nMap;
			for (auto& pair : map)
			{
				nMap[std::get<0>(pair.second)] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFTYPE(x, y) { EventType::x, std::make_tuple(SDL_##y, #x), }
	
	static std::map<EventType, std::tuple<SDL_EventType, std::string>> types = {
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
		#if SDL_VERSION_MIN(2, 0, 5)
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
	
	#endif
	
	
	unsigned int SDL_RawEventType(EventType type)
	{
		#ifdef QUTILS_HAS_SDL2
		#ifdef DEBUG
		try
		{
		#endif
		return std::get<0>(types.at(type));
		#ifdef DEBUG
		}
		catch (std::exception& ex)
		{
			std::cout << "\nCould not find raw equivalent for " << (int)type << "\n";
			throw;
		}
		#endif
		#else
		throw NotAvail();
		#endif
	}
	
	EventType SDL_EnumEventType(unsigned int type)
	{
		#ifdef QUTILS_HAS_SDL2
		#ifdef DEBUG
		try
		{
		#endif
		return revTypes.at((SDL_EventType)type);
		#ifdef DEBUG
		}
		catch (std::exception& ex)
		{
			std::cout << "\nCould not find enum equivalent for " << (int)type << "\n";
			throw;
		}
		#endif
		#else
		throw NotAvail();
		#endif
	}
	
	std::string SDL_EventTypeName(EventType type)
	{
		#ifdef QUTILS_HAS_SDL2
		return std::get<1>(types.at(type));
		#else
		throw NotAvail();
		#endif
	}
}