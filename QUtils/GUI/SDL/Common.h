#pragma once

/*typedef int8_t		Sint8;
typedef uint8_t		Uint8;
typedef int16_t		Sint16;
typedef uint16_t	Uint16;
typedef int32_t		Sint32;
typedef uint32_t	Uint32;*/

//#define _SDL_stdinc_h
//#define _SDL_error_h
//#define _SDL_active_h
//#define _SDL_keyboard_h
//#define _SDL_mouse_h
//#define _SDL_joystick_h
//#define _SDL_quit_h

//#include <SDL2/SDL_events.h>
//#include <SDL


namespace QUtils::GUI::SDL
{
	//typedef SDL_EventType EventType;
	enum EventType
	{
		FirstEvent     = 0,     /**< Unused (do not remove) */

    /* Application events */
    Quit           = 0x100, /**< User-requested quit */

    /* These application events have special meaning on iOS, see README-ios.md for details */
    App_Terminating,        /**< The application is being terminated by the OS
                                     Called on iOS in applicationWillTerminate()
                                     Called on Android in onDestroy()
                                */
    App_LowMemory,          /**< The application is low on memory, free memory if possible.
                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                     Called on Android in onLowMemory()
                                */
    App_WillEnterBackground, /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                */
    App_DidEnterBackground, /**< The application did enter the background and may not get CPU for some time
                                     Called on iOS in applicationDidEnterBackground()
                                     Called on Android in onPause()
                                */
    App_WillEnterForeground, /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                */
    App_DidEnterForeground, /**< The application is now interactive
                                     Called on iOS in applicationDidBecomeActive()
                                     Called on Android in onResume()
                                */

    /* Window events */
    WindowEvent    = 0x200, /**< Window state change */
    SYSWMEvent,             /**< System specific event */

    /* Keyboard events */
    KeyDown        = 0x300, /**< Key pressed */
    KeyUp,                  /**< Key released */
    TextEditing,            /**< Keyboard text editing (composition) */
    TextInput,              /**< Keyboard text input */
    KeymapChanged,          /**< Keymap changed due to a system event such as an
                                     input language or keyboard layout change.
                                */

    /* Mouse events */
    MouseMotion    = 0x400, /**< Mouse moved */
    MouseButtonDown,        /**< Mouse button pressed */
    MouseButtonUp,          /**< Mouse button released */
    MouseWheel,             /**< Mouse wheel motion */

    /* Joystick events */
    JoyAxisMotion  = 0x600, /**< Joystick axis motion */
    JoyBallMotion,          /**< Joystick trackball motion */
    JoyHatMotion,           /**< Joystick hat position change */
    JoyButtonDown,          /**< Joystick button pressed */
    JoyButtonUp,            /**< Joystick button released */
    JoyDeviceAdded,         /**< A new joystick has been inserted into the system */
    JoyDeviceRemoved,       /**< An opened joystick has been removed */

    /* Game controller events */
    ControllerAxisMotion  = 0x650, /**< Game controller axis motion */
    ControllerButtonDown,          /**< Game controller button pressed */
    ControllerButtonUp,            /**< Game controller button released */
    ControllerDeviceAdded,         /**< A new Game controller has been inserted into the system */
    ControllerDeviceRemoved,       /**< An opened Game controller has been removed */
    ControllerDeviceRemapped,      /**< The controller mapping was updated */

    /* Touch events */
    FingerDown      = 0x700,
    FingerUp,
    FingerMotion,

    /* Gesture events */
    DollarGesture   = 0x800,
    DollarRecord,
    MultiGesture,

    /* Clipboard events */
    ClipboardUpdate = 0x900, /**< The clipboard changed */

    /* Drag and drop events */
    DropFile        = 0x1000, /**< The system requests a file open */
    DropText,                 /**< text/plain drag-and-drop event */
    DropBegin,                /**< A new set of drops is beginning (NULL filename) */
    DropComplete,             /**< Current set of drops is now complete (NULL filename) */

    /* Audio hotplug events */
    AudioDeviceAdded = 0x1100, /**< A new audio device is available */
    AudioDeviceRemoved,        /**< An audio device has been removed. */

    /* Render events */
    Render_Targets_Reset = 0x2000, /**< The render targets have been reset and their contents need to be updated */
    Render_Device_Reset, /**< The device has been reset and all textures need to be recreated */

    /** Events ::UserEvent through ::LASTEvent are for your use,
     *  and should be allocated with RegisterEvents()
     */
    UserEvent    = 0x8000,

    /**
     *  This last event is only for bounding internal arrays
     */
    LastEvent    = 0xFFFF
};
}