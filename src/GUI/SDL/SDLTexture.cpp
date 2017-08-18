#include <QUtils/GUI/SDL/SDLTexture.h>
#include <QUtils/GUI/SDL/SDLWindow.h>
#include <QUtils/GUI/SDL/Errors.h>

#ifdef QUTILS_HAS_SDL2

#include <SDL2/SDL.h>

#else

#include <QUtils/Exception/NotAvailable.h>

#endif

namespace QUtils::GUI::SDL
{
	SDLTexture::SDLTexture(SDLWindow* win) : Texture(), SDLWindowChild(win), tex(nullptr), ren(nullptr)
	{}
	
	
	SDLTexture::SDLTexture(SDLWindow* win, const int w, const int h) : Texture(), SDLWindowChild(win), tex(nullptr), ren(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		
		ren = win->renderer();
		tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET, w, h);
		if (tex == NULL)
		{
			SDL_THROWERROR();
		}
		#else
		throw NotAvail();
		#endif
	}
	
	SDLTexture::SDLTexture(SDLWindow* win, SDL_Surface* surf) : Texture(), SDLWindowChild(win), tex(NULL), ren(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		ren = window->renderer();
		tex = SDL_CreateTextureFromSurface(ren, surf);
		if (tex == NULL)
		{
			SDL_THROWERROR();
		}
		
		
		#else
		throw NotAvail();
		#endif
	}
	
	SDLTexture::~SDLTexture()
	{
		if (tex != NULL)
		{
			SDL_DestroyTexture(tex);
		}
	}
	
	
	
	void SDLTexture::fillRect(int x, int y, int w, int h, int r, int g, int b, int alpha)
	{
		SDL_Rect rect = { x, y, w, h };
		if (SDL_GetRenderTarget(ren) != tex)
		{
		SDL_CHECKERROR(SDL_SetRenderTarget(ren, tex), 0);
		}
		SDL_CHECKERROR(SDL_SetRenderDrawColor(ren, r, g, b, alpha), 0);
		SDL_CHECKERROR(SDL_RenderFillRect(ren, &rect), 0);
		//SDL_CHECKERROR(SDL_SetRenderTarget(ren, NULL), 0);
		//SDL_CHECKERROR(SDL_RenderCopy(ren, tex, NULL, NULL), 0);
		//SDL_RenderPresent(ren);
		SDL_IFERROR();
		 
	}
	
	void SDLTexture::render(int x, int y, int w, int h)
	{
		SDL_Rect rect = { x, y, w, h };
		SDL_CHECKERROR(SDL_RenderCopy(ren, tex, NULL, &rect), 0);
	}
	
	
	void SDLTexture::placeTexture(Texture* tex, int x, int y, int w, int h)
	{
		SDL_Rect rect = { x, y, w, h };
		if (SDL_GetRenderTarget(ren) != this->tex)
		{
		SDL_CHECKERROR(SDL_SetRenderTarget(ren, this->tex), 0);
		}
		SDL_CHECKERROR(SDL_RenderCopy(ren, ((SDLTexture*)tex)->tex, NULL, &rect), 0);
	}
	
	void SDLTexture::update()
	{
		if (SDL_GetRenderTarget(ren) != tex)
		{
		SDL_CHECKERROR(SDL_SetRenderTarget(ren, tex), 0);
		}
		SDL_RenderPresent(ren);
	}
	
	void SDLTexture::clear(int r, int g, int b)
	{
		if (SDL_GetRenderTarget(ren) != tex)
		{
		SDL_CHECKERROR(SDL_SetRenderTarget(ren, tex), 0);
		}
		SDL_CHECKERROR(SDL_SetRenderDrawColor(ren, r, g, b, 255), 0);
		SDL_CHECKERROR(SDL_RenderClear(ren), 0);
	}
}