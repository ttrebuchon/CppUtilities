#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Surface::Surface() : Base(NULL)
	{
		
	}
	
	
	
	
	Surface::Surface(SDL_Surface* ptr) : Base(ptr)
	{
		
	}
	
	
	
	
	
	
	Surface::Surface(int w, int h, int depth, unsigned int Rmask, unsigned int Gmask, unsigned int Bmask, unsigned int Amask) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateRGBSurface(0, w, h, depth, Rmask, Gmask, Bmask, Amask), NULL);
		setInstance(ptr, this);
	}
	
	Surface::Surface(int w, int h, PixelFormat format) : Base(NULL)
	{
		unsigned int Rmask, Gmask, Bmask, Amask;
		int depth;
		SDL_CHECKERROR(SDL_PixelFormatEnumToMasks(SDL_RawPixelFormat(format), &depth, &Rmask, &Gmask, &Bmask, &Amask), SDL_TRUE);
		SDL_ERRORIF(ptr = SDL_CreateRGBSurface(0, w, h, depth, Rmask, Gmask, Bmask, Amask), NULL);
		setInstance(ptr, this);
	}
	
	Surface::~Surface()
	{
		if (ptr != NULL)
		{
			SDL_FreeSurface(ptr);
		}
	}
	
	
	
	
	Texture* Surface::createTexture(Renderer* ren) const
	{
		SDL_Texture* texPtr;
		SDL_ERRORIF(texPtr = SDL_CreateTextureFromSurface(**ren, ptr), NULL);
		return Texture::getObject(texPtr);
	}
	
	Renderer* Surface::createSoftwareRenderer() const
	{
		SDL_Renderer* ren = NULL;
		SDL_ERRORIF(ren = SDL_CreateSoftwareRenderer(ptr), NULL);
		return Renderer::getObject(ren);
	}
	
	const SDL_PixelFormat* Surface::format() const
	{
		return ptr->format;
	}
	
	int Surface::width() const
	{
		return ptr->w;
	}
	
	int Surface::height() const
	{
		return ptr->h;
	}
	
	int Surface::pitch() const
	{
		return ptr->pitch;
	}
	
	void*& Surface::pixels()
	{
		return ptr->pixels;
	}
	
	const void* Surface::pixels() const
	{
		return ptr->pixels;
	}
	
	void*& Surface::userdata()
	{
		return ptr->userdata;
	}
	
	const void* Surface::userdata() const
	{
		return ptr->userdata;
	}
	
	int& Surface::refcount()
	{
		return ptr->refcount;
	}
	
	const int& Surface::refcount() const
	{
		return ptr->refcount;
	}
	
	SDL_Rect* Surface::clip_rect()
	{
		return &ptr->clip_rect;
	}
	
	const SDL_Rect* Surface::clip_rect() const
	{
		return &ptr->clip_rect;
	}
	
	void Surface::setRLE(bool value)
	{
		SDL_CHECKERROR(SDL_SetSurfaceRLE(ptr, value), 0);
	}
	
	void Surface::lock()
	{
		SDL_CHECKERROR(SDL_LockSurface(ptr), 0);
	}
	
	void Surface::unlock()
	{
		SDL_UnlockSurface(ptr);
	}
	
	bool Surface::mustLock() const
	{
		return SDL_MUSTLOCK(ptr) == SDL_TRUE;
	}
	
	void Surface::blitTo(Surface* surf, const SDL_Rect* src, SDL_Rect* dst) const
	{
		SDL_CHECKERROR(SDL_BlitSurface(ptr, src, **surf, dst), 0);
	}
	
	void Surface::blitToScaled(Surface* surf, const SDL_Rect* src, SDL_Rect* dst) const
	{
		SDL_CHECKERROR(SDL_BlitScaled(ptr, src, **surf, dst), 0);
	}
	
	void Surface::blitTo(Surface* surf, const Rect* src, Rect* dst) const
	{
		SDL_CHECKERROR(SDL_BlitSurface(ptr, (const SDL_Rect*)src, **surf, (SDL_Rect*)dst), 0);
	}
	
	void Surface::blitToScaled(Surface* surf, const Rect* src, Rect* dst) const
	{
		SDL_CHECKERROR(SDL_BlitScaled(ptr, (const SDL_Rect*)src, **surf, (SDL_Rect*)dst), 0);
	}
	
	
}