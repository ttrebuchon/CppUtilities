#include <QUtils/GUI/SDL/SDLSurface.h>
#include <QUtils/GUI/SDL/SDLWindow.h>
#include <QUtils/GUI/SDL/SDLTexture.h>
#include <QUtils/GUI/SDL/Errors.h>

#include <QUtils/Exception/NotImplemented.h>

#ifdef QUTILS_HAS_SDL2

#include <SDL2/SDL.h>

#else

#include <QUtils/Exception/NotAvailable.h>

#endif


namespace QUtils::GUI::SDL
{
	SDLSurface::SDLSurface(SDLWindow* win, SDL_Surface* surf, bool owned) : Surface(), SDLWindowChild(win), surf(surf), owned(owned), _ren(NULL)
	{
		
	}
	
	SDLSurface::~SDLSurface()
	{
		if (owned && surf != NULL)
		{
			SDL_FreeSurface(surf);
		}
	}
	
	
	//Protected
	void SDLSurface::createRenderer()
	{
		SDL_ERRORIF(_ren = SDL_CreateSoftwareRenderer(surf), NULL);
	}
	
	
	//Public
	void SDLSurface::copyTo(SDLSurface* s2) const
	{
		SDL_BlitSurface(surf, NULL, s2->surf, NULL);
	}
	
	SDLTexture* SDLSurface::toTexture() const
	{
		return new SDLTexture(window, surf);
	}
	
	
	
	
	
}