#include <QUtils/Drawing/SDL/Window.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/Version.h>
#include <QUtils/Exception/NotImplemented.h>

#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Window::Window() : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	Window::Window(SDL_Window* ptr) : Base(ptr)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	Window::Window(const std::string title, int x, int y, int w, int h, WindowFlags flags) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ERRORIF(ptr = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_RawWindowFlags(flags)), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Window::Window(const void* data) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ERRORIF(ptr = SDL_CreateWindowFrom(data), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Window::~Window()
	{
		#ifdef QUTILS_HAS_SDL2
		if (ptr != NULL)
		{
			SDL_DestroyWindow(ptr);
		}
		#endif
	}
	
	#if QUTILS_SDL_VERSION_HIDE(2,0,5)
	int Window::bordersSize(int* top, int* left, int* bottom, int* right) const
	{
		#if SDL_VERSION_MIN(2,0,5)
		return SDL_GetWindowBordersSize(ptr, top, left, bottom, right);
		#else
		throw NotAvail();
		#endif
	}
	#endif
	
	float Window::brightness() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowBrightness(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::brightness(float value) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowBrightness(ptr, value);
		#else
		throw NotAvail();
		#endif
	}
	
	void* Window::data(const std::string name) const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowData(ptr, name.c_str());
		#else
		throw NotAvail();
		#endif
	}
	
	int Window::displayIndex() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowDisplayIndex(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	unsigned int Window::flags() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowFlags(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	Window* Window::GetFromID(unsigned int id)
	{
		#ifdef QUTILS_HAS_SDL2
		auto ptr = SDL_GetWindowFromID(id);
		return Window::getObject(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	
	unsigned int Window::ID() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowID(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::maximumSize(int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_GetWindowMaximumSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::minimumSize(int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_GetWindowMinimumSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::setMaximumSize(int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowMaximumSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::setMinimumSize(int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowMinimumSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	#if QUTILS_SDL_VERSION_HIDE(2,0,5)
	float Window::opacity() const
	{
		#if SDL_VERSION_MIN(2,0,5)
		float val;
		SDL_GetWindowOpacity(ptr, &val);
		return val;
		#else
		throw NotAvail();
		#endif
	}
	#endif
	
	unsigned int Window::pixelFormat() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowPixelFormat(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::position(int* x, int* y) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_GetWindowPosition(ptr, x, y);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::setPosition(int x, int y)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowPosition(ptr, x, y);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::size(int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_GetWindowSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::setSize(int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Window::surface() const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		SDL_ERRORIF(surfPtr = SDL_GetWindowSurface(ptr), NULL);
		auto surf = Surface::getObject(surfPtr);
		if (surf != NULL)
		{
			surf->setWindowSurface(true);
		}
		return surf;
		#else
		throw NotAvail();
		#endif
	}
	
	std::string Window::title() const
	{
		#ifdef QUTILS_HAS_SDL2
		return std::string(SDL_GetWindowTitle(ptr));
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::title(const std::string title)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowTitle(ptr, title.c_str());
		#else
		throw NotAvail();
		#endif
	}
	
	bool Window::visible() const
	{
		#ifdef QUTILS_HAS_SDL2
		auto flags = this->flags();
		return ((flags & SDL_WINDOW_SHOWN) > 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::show()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ShowWindow(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::hide()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_HideWindow(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::maximize()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_MaximizeWindow(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::minimize()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_MinimizeWindow(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::raise()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RaiseWindow(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::restore()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RestoreWindow(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Window::fullscreen() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ((this->flags() & SDL_WINDOW_FULLSCREEN) > 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::fullscreen(bool value)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowFullscreen(ptr, (value ? SDL_WINDOW_FULLSCREEN : 0));
		#else
		throw NotAvail();
		#endif
	}
	
	bool Window::fullscreenDesktop() const
	{
		#ifdef QUTILS_HAS_SDL2
		return ((this->flags() & SDL_WINDOW_FULLSCREEN_DESKTOP) > 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::fullscreenDesktop(bool value)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowFullscreen(ptr, (value ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
		#else
		throw NotAvail();
		#endif
	}
	
	bool Window::grabbed() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetWindowGrab(ptr) == SDL_TRUE;
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::grabbed(bool value)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowGrab(ptr, (value ? SDL_TRUE : SDL_FALSE));
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::setIcon(Surface* surf)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetWindowIcon(ptr, **surf);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::updateSurface()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_UpdateWindowSurface(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::updateSurface(int x, int y, int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Rect rect = { x, y, w, h };
		SDL_UpdateWindowSurfaceRects(ptr, &rect, 1);
		#else
		throw NotAvail();
		#endif
	}
	
	void Window::updateSurfaceRects(const SDL_Rect* rects, int count)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_UpdateWindowSurfaceRects(ptr, rects, count);
		#else
		throw NotAvail();
		#endif
	}
	
	Renderer* Window::renderer() const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Renderer* renPtr;
		SDL_ERRORIF(renPtr = SDL_GetRenderer(ptr), NULL);
		return Renderer::getObject(renPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	int Window::width() const
	{
		#ifdef QUTILS_HAS_SDL2
		int w;
		SDL_GetWindowSize(ptr, &w, NULL);
		return w;
		#else
		throw NotAvail();
		#endif
	}
	
	int Window::height() const
	{
		#ifdef QUTILS_HAS_SDL2
		int h;
		SDL_GetWindowSize(ptr, NULL, &h);
		return h;
		#else
		throw NotAvail();
		#endif
	}
	
	int Window::x() const
	{
		#ifdef QUTILS_HAS_SDL2
		int x;
		SDL_GetWindowPosition(ptr, &x, NULL);
		return x;
		#else
		throw NotAvail();
		#endif
	}
	
	int Window::y() const
	{
		#ifdef QUTILS_HAS_SDL2
		int y;
		SDL_GetWindowPosition(ptr, NULL, &y);
		return y;
		#else
		throw NotAvail();
		#endif
	}
	
	
}