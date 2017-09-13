#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"
#include <QUtils/Drawing/SDL/Version.h>


namespace QUtils::Drawing::SDL
{
	Surface::Surface() : Base(NULL), windowSurface(false)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	Surface::Surface(SDL_Surface* ptr) : Base(ptr), windowSurface(false)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	
	void Surface::setWindowSurface(bool val)
	{
		windowSurface = val;
	}
	
	
	
	
	
	
	Surface::Surface(int w, int h, int depth, unsigned int Rmask, unsigned int Gmask, unsigned int Bmask, unsigned int Amask) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ERRORIF(ptr = SDL_CreateRGBSurface(0, w, h, depth, Rmask, Gmask, Bmask, Amask), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface::Surface(int w, int h, PixelFormat format) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		unsigned int Rmask, Gmask, Bmask, Amask;
		int depth;
		SDL_CHECKERROR(SDL_PixelFormatEnumToMasks(SDL_RawPixelFormat(format), &depth, &Rmask, &Gmask, &Bmask, &Amask), SDL_TRUE);
		SDL_ERRORIF(ptr = SDL_CreateRGBSurface(0, w, h, depth, Rmask, Gmask, Bmask, Amask), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface::~Surface()
	{
		#ifdef QUTILS_HAS_SDL2
		if (ptr != NULL && !windowSurface)
		{
			SDL_FreeSurface(ptr);
		}
		#endif
	}
	
	
	
	
	Texture* Surface::createTexture(Renderer* ren) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Texture* texPtr;
		SDL_ERRORIF(texPtr = SDL_CreateTextureFromSurface(**ren, ptr), NULL);
		return Texture::getObject(texPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Renderer* Surface::createSoftwareRenderer() const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Renderer* ren = NULL;
		SDL_ERRORIF(ren = SDL_CreateSoftwareRenderer(ptr), NULL);
		return Renderer::getObject(ren);
		#else
		throw NotAvail();
		#endif
	}
	
	const SDL_PixelFormat* Surface::format() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->format;
		#else
		throw NotAvail();
		#endif
	}
	
	int Surface::width() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->w;
		#else
		throw NotAvail();
		#endif
	}
	
	int Surface::height() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->h;
		#else
		throw NotAvail();
		#endif
	}
	
	int Surface::pitch() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->pitch;
		#else
		throw NotAvail();
		#endif
	}
	
	void*& Surface::pixels()
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->pixels;
		#else
		throw NotAvail();
		#endif
	}
	
	const void* Surface::pixels() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->pixels;
		#else
		throw NotAvail();
		#endif
	}
	
	void*& Surface::userdata()
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->userdata;
		#else
		throw NotAvail();
		#endif
	}
	
	const void* Surface::userdata() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->userdata;
		#else
		throw NotAvail();
		#endif
	}
	
	int& Surface::refcount()
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->refcount;
		#else
		throw NotAvail();
		#endif
	}
	
	const int& Surface::refcount() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ptr->refcount;
		#else
		throw NotAvail();
		#endif
	}
	
	SDL_Rect* Surface::clip_rect()
	{
		#ifdef QUTILS_HAS_SDL2
		return &ptr->clip_rect;
		#else
		throw NotAvail();
		#endif
	}
	
	const SDL_Rect* Surface::clip_rect() const
	{
		#ifdef QUTILS_HAS_SDL2
		return &ptr->clip_rect;
		#else
		throw NotAvail();
		#endif
	}
	
	void Surface::setRLE(bool value)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_SetSurfaceRLE(ptr, value), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Surface::lock()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_LockSurface(ptr), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Surface::unlock()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_UnlockSurface(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Surface::mustLock() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_MUSTLOCK(ptr) == SDL_TRUE;
		#else
		throw NotAvail();
		#endif
	}
	
	void Surface::blitTo(Surface* surf, const SDL_Rect* src, SDL_Rect* dst) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_BlitSurface(ptr, src, **surf, dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Surface::blitToScaled(Surface* surf, const SDL_Rect* src, SDL_Rect* dst) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_BlitScaled(ptr, src, **surf, dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Surface::blitTo(Surface* surf, const Rect* src, Rect* dst) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_BlitSurface(ptr, (const SDL_Rect*)src, **surf, (SDL_Rect*)dst), 0);
		#else
		throw NotAvail();
		#endif
		
	}
	
	void Surface::blitToScaled(Surface* surf, const Rect* src, Rect* dst) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_BlitScaled(ptr, (const SDL_Rect*)src, **surf, (SDL_Rect*)dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	
}