#include <QUtils/Drawing/SDL/Window.h>
#include <QUtils/Exception/NotImplemented.h>

#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Window::Window() : ptr(NULL)
	{
		
	}
	
	
	
	Window::Window(const std::string title, int x, int y, int w, int h, unsigned int flags) : ptr(NULL)
	{
		ptr = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	}
	
	Window::Window(const void* data) : ptr(NULL)
	{
		ptr = SDL_CreateWindowFrom(data);
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
		if (ptr == NULL)
		{
			return NULL;
		}
		auto win = new Window();
		win->ptr = ptr;
		return win;
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
	
	void Window::size(int* w, int* h) const
	{
		SDL_GetWindowSize(ptr, w, h);
	}
	
	std::string Window::title() const
	{
		return std::string(SDL_GetWindowTitle(ptr));
	}
	
	
}