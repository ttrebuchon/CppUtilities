#pragma once
#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace GUI
{
namespace SDL
{
	QUTILS_CUSTOM_EXCEPTION(SDLErrorException,);
}
}
}

#define SDL_THROWERROR() throw ::QUtils::GUI::SDL::SDLErrorException().Function(__func__).Msg(std::string("SDL Error: ") + SDL_GetError())

#define SDL_CHECKERROR(op, expected) SDL_ClearError(); if ((op) != (expected)) { SDL_THROWERROR(); }

#define SDL_IFERROR() if (std::string(SDL_GetError()) != "") { SDL_THROWERROR(); }

#define SDL_ERRORIF(op, err) SDL_ClearError(); if ((op) == (err)) { SDL_THROWERROR(); }