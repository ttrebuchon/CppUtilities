#ifdef QUTILS_HAS_SDL2
#include <SDL2/SDL_version.h>


#if SDL_VERSION_ATLEAST(2,0,5)
#define SDL_2_0_5
#endif


#define SDL_VERSION_MIN(x, y, z) SDL_VERSION_ATLEAST(x, y, z)


#else

#define SDL_VERSION_MIN(x, y, z) FALSE

#endif