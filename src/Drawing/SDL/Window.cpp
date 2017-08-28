#include <QUtils/Drawing/SDL/Window.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Exception/NotImplemented.h>

#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Window::Window() : Base(NULL)
	{
		
	}
	
	
	
	
	Window::Window(SDL_Window* ptr) : Base(ptr)
	{
		
	}
	
	Window::Window(const std::string title, int x, int y, int w, int h, WindowFlags flags) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_RawWindowFlags(flags)), NULL);
		setInstance(ptr, this);
	}
	
	Window::Window(const void* data) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateWindowFrom(data), NULL);
		setInstance(ptr, this);
	}
	
	Window::~Window()
	{
		if (ptr != NULL)
		{
			SDL_DestroyWindow(ptr);
		}
	}
	
	int Window::bordersSize(int* top, int* left, int* bottom, int* right) const
	{
		throw NotImp();
		//return SDL_GetWindowBordersSize(ptr, top, left, bottom, right);
	}
	
	float Window::brightness() const
	{
		return SDL_GetWindowBrightness(ptr);
	}
	
	void Window::brightness(float value) const
	{
		SDL_SetWindowBrightness(ptr, value);
	}
	
	void* Window::data(const std::string name) const
	{
		return SDL_GetWindowData(ptr, name.c_str());
	}
	
	int Window::displayIndex() const
	{
		return SDL_GetWindowDisplayIndex(ptr);
	}
	
	unsigned int Window::flags() const
	{
		return SDL_GetWindowFlags(ptr);
	}
	
	Window* Window::GetFromID(unsigned int id)
	{
		auto ptr = SDL_GetWindowFromID(id);
		return Window::getObject(ptr);
	}
	
	
	unsigned int Window::ID() const
	{
		return SDL_GetWindowID(ptr);
	}
	
	void Window::maximumSize(int* w, int* h) const
	{
		SDL_GetWindowMaximumSize(ptr, w, h);
	}
	
	void Window::minimumSize(int* w, int* h) const
	{
		SDL_GetWindowMinimumSize(ptr, w, h);
	}
	
	void Window::setMaximumSize(int w, int h)
	{
		SDL_SetWindowMaximumSize(ptr, w, h);
	}
	
	void Window::setMinimumSize(int w, int h)
	{
		SDL_SetWindowMinimumSize(ptr, w, h);
	}
	
	float Window::opacity() const
	{
		throw NotImp();
		/*
		float val;
		SDL_GetWindowOpacity(ptr, &val);
		return val;*/
	}
	
	unsigned int Window::pixelFormat() const
	{
		return SDL_GetWindowPixelFormat(ptr);
	}
	
	void Window::position(int* x, int* y) const
	{
		SDL_GetWindowPosition(ptr, x, y);
	}
	
	void Window::setPosition(int x, int y)
	{
		SDL_SetWindowPosition(ptr, x, y);
	}
	
	void Window::size(int* w, int* h) const
	{
		SDL_GetWindowSize(ptr, w, h);
	}
	
	void Window::setSize(int w, int h)
	{
		SDL_SetWindowSize(ptr, w, h);
	}
	
	Surface* Window::surface() const
	{
		SDL_Surface* surfPtr;
		SDL_ERRORIF(surfPtr = SDL_GetWindowSurface(ptr), NULL);
		auto surf = Surface::getObject(surfPtr);
		if (surf != NULL)
		{
			surf->setWindowSurface(true);
		}
		return surf;
		
	}
	
	std::string Window::title() const
	{
		return std::string(SDL_GetWindowTitle(ptr));
	}
	
	void Window::title(const std::string title)
	{
		SDL_SetWindowTitle(ptr, title.c_str());
	}
	
	bool Window::visible() const
	{
		auto flags = this->flags();
		return ((flags & SDL_WINDOW_SHOWN) > 0);
	}
	
	void Window::show()
	{
		SDL_ShowWindow(ptr);
	}
	
	void Window::hide()
	{
		SDL_HideWindow(ptr);
	}
	
	void Window::maximize()
	{
		SDL_MaximizeWindow(ptr);
	}
	
	void Window::minimize()
	{
		SDL_MinimizeWindow(ptr);
	}
	
	void Window::raise()
	{
		SDL_RaiseWindow(ptr);
	}
	
	void Window::restore()
	{
		SDL_RestoreWindow(ptr);
	}
	
	bool Window::fullscreen() const
	{
		return ((this->flags() & SDL_WINDOW_FULLSCREEN) > 0);
	}
	
	void Window::fullscreen(bool value)
	{
		SDL_SetWindowFullscreen(ptr, (value ? SDL_WINDOW_FULLSCREEN : 0));
	}
	
	bool Window::fullscreenDesktop() const
	{
		return ((this->flags() & SDL_WINDOW_FULLSCREEN_DESKTOP) > 0);
	}
	
	void Window::fullscreenDesktop(bool value)
	{
		SDL_SetWindowFullscreen(ptr, (value ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
	}
	
	bool Window::grabbed() const
	{
		return SDL_GetWindowGrab(ptr) == SDL_TRUE;
	}
	
	void Window::grabbed(bool value)
	{
		SDL_SetWindowGrab(ptr, (value ? SDL_TRUE : SDL_FALSE));
	}
	
	void Window::setIcon(Surface* surf)
	{
		SDL_SetWindowIcon(ptr, **surf);
	}
	
	void Window::updateSurface()
	{
		SDL_UpdateWindowSurface(ptr);
	}
	
	void Window::updateSurface(int x, int y, int w, int h)
	{
		SDL_Rect rect = { x, y, w, h };
		SDL_UpdateWindowSurfaceRects(ptr, &rect, 1);
	}
	
	void Window::updateSurfaceRects(const SDL_Rect* rects, int count)
	{
		SDL_UpdateWindowSurfaceRects(ptr, rects, count);
	}
	
	Renderer* Window::renderer() const
	{
		SDL_Renderer* renPtr;
		SDL_ERRORIF(renPtr = SDL_GetRenderer(ptr), NULL);
		return Renderer::getObject(renPtr);
	}
	
	int Window::width() const
	{
		int w;
		SDL_GetWindowSize(ptr, &w, NULL);
		return w;
	}
	
	int Window::height() const
	{
		int h;
		SDL_GetWindowSize(ptr, NULL, &h);
		return h;
	}
	
	int Window::x() const
	{
		int x;
		SDL_GetWindowPosition(ptr, &x, NULL);
		return x;
	}
	
	int Window::y() const
	{
		int y;
		SDL_GetWindowPosition(ptr, NULL, &y);
		return y;
	}
	
	
}