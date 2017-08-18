#include <QUtils/GUI/SDL/SDLWindow.h>
#include <QUtils/GUI/SDL/Errors.h>
#include <QUtils/GUI/SDL/Common.h>
#include <QUtils/GUI/SDL/SDLSurface.h>

#include <iostream>
#include <QUtils/Output/HexObject.h>

#include <QUtils/Exception/NotImplemented.h>

#ifdef QUTILS_HAS_SDL2

#include <SDL2/SDL.h>

#else

#include <QUtils/Exception/NotAvailable.h>

#endif

namespace QUtils::GUI::SDL
{
	SDLWindow::SDLWindow(const std::string title, const int x, const int y, const int w, const int h) : Window(), win(NULL), ren(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			throw SDLErrorException().Function(__func__).Msg(SDL_GetError());
		}
		//win = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
		win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if (win == NULL)
		{
			throw SDLErrorException().Function(__func__).Msg(SDL_GetError());
		}
		
		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		if (ren == NULL)
		{
			throw SDLErrorException().Function(__func__).Msg(SDL_GetError());
		}
		SDL_ClearError();
		SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
		/*SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_Rect rect = {w/4, h/4, w/2, h/2};
		SDL_RenderFillRect(ren, &rect);*/
		
		#else
		throw NotAvail();
		#endif
	}
	
	SDLWindow::~SDLWindow()
	{
		
		#ifdef QUTILS_HAS_SDL2
		if (win != NULL)
		{
			SDL_DestroyWindow(win);
		}
		if (ren != NULL)
		{
			SDL_free(ren);
		}
		
		//SDL_Quit();
		#endif
	}
	
	int SDLWindow::width() const
	{
		#ifdef QUTILS_HAS_SDL2
		int w = -1;
		int h = -1;
		SDL_GetWindowSize(win, &w, &h);
		return w;
		#else
		throw NotAvail();
		#endif
	}
	
	int SDLWindow::height() const
	{
		#ifdef QUTILS_HAS_SDL2
		int w = -1;
		int h = -1;
		SDL_GetWindowSize(win, &w, &h);
		return h;
		#else
		throw NotAvail();
		#endif
	}
	
	int SDLWindow::x() const
	{
		#ifdef QUTILS_HAS_SDL2
		int x = -1;
		int y = -1;
		SDL_GetWindowPosition(win, &x, &y);
		return x;
		#else
		throw NotAvail();
		#endif
	}
	
	int SDLWindow::y() const
	{
		#ifdef QUTILS_HAS_SDL2
		int x = -1;
		int y = -1;
		SDL_GetWindowPosition(win, &x, &y);
		return y;
		#else
		throw NotAvail();
		#endif
	}
	
	SDLTexture* SDLWindow::createTexture(const int w, const int h)
	{
		#ifdef QUTILS_HAS_SDL2
		return new SDLTexture(this, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	SDLSurface* SDLWindow::createSurface(int w, int h, int depth, int rmask, int gmask, int bmask, int alphamask)
	{
		SDL_Surface* surf;
		SDL_ERRORIF(surf = SDL_CreateRGBSurface(0, w, h, depth, rmask, gmask, bmask, alphamask), NULL);
		return new SDLSurface(this, surf, true);
	}
	
	void SDLWindow::placeTexture(Texture* tex, int x, int y, int w, int h)
	{
		if (SDL_GetRenderTarget(ren) != NULL)
		{
			SDL_SetRenderTarget(ren, NULL);
		}
		
		((SDLTexture*)tex)->render(x, y, w, h);
	}
	
	void SDLWindow::update()
	{
		#ifdef QUTILS_HAS_SDL2
		//TODO
		//SDL_CHECKERROR(SDL_UpdateWindowSurface(win), 0);
		
		if (SDL_GetRenderTarget(ren) != NULL)
		{
			SDL_CHECKERROR(SDL_SetRenderTarget(ren, NULL), 0);
		}
		
		SDL_ClearError();
		SDL_RenderPresent(ren);
		SDL_IFERROR();
		#else
		throw NotAvail();
		#endif
	}
	
	void SDLWindow::handleEvents()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			auto flags = std::cerr.flags();
			std::cerr << "Event: 0x" << std::hex << e.type << "\n";
			std::cerr.flags(flags);
			//Ignore joystick events
			if (e.type >= 0x600 && e.type <= 0x606)
			{
				continue;
			}
			switch ((EventType)e.type)
			{
				case Quit:
				onQuit();
				break;
				
				case WindowEvent:
				{
					auto wflags = std::cerr.flags();
					SDL_WindowEvent ev = e.window;
					std::cerr << "Window Event: 0x" << std::hex << (unsigned int)ev.event << "\n";
					std::cerr.flags(wflags);
					//throw SDLErrorException().Msg(std::to_string(ev.type));
				}
				break;
				
				case KeyDown:
				onKeyDown();
				break;
				
				case FingerDown:
				{
					SDL_TouchFingerEvent ev = e.tfinger;
					
					onFingerDown(ev.timestamp, ev.touchId, ev.fingerId, ev.x, ev.y, ev.dx, ev.dy, ev.pressure);
				}
				break;
				
				default:
				//throw SDLErrorException().Msg(std::to_string(e.type));
				//throw NotImp();
				break;
			}
		}
		#else
		throw NotAvail();
		#endif
	}
	
	SDLSurface* SDLWindow::windowSurface()
	{
		#ifdef QUTILS_HAS_SDL2
		auto surf = new SDLSurface(this, SDL_GetWindowSurface(win), false);
		return surf;
		#else
		throw NotAvail();
		#endif
	}
	
	const SDL_Renderer* SDLWindow::renderer() const
	{
		return ren;
	}
		
	SDL_Renderer* SDLWindow::renderer()
	{
		return ren;
	}
	
	void SDLWindow::clear(int r, int g, int b)
	{
		SDL_SetRenderDrawColor(ren, r, g, b, 255);
		if (SDL_GetRenderTarget(ren) != NULL)
		{
			SDL_SetRenderTarget(ren, NULL);
		}
		SDL_RenderClear(ren);
	}
	
	SDL_Window* SDLWindow::operator*()
	{
		return win;
	}
	
}