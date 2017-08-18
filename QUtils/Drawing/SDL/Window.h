#pragma once
#include <string>

class SDL_Window;

namespace QUtils::Drawing::SDL
{
	class Surface;
	
	class Window
	{
		protected:
		SDL_Window* ptr;
		Window();
		
		public:
		Window(const std::string title, int x, int y, int w, int h, unsigned int flags);
		Window(const void* data);
		virtual ~Window();
		
		int bordersSize(int* top, int* left, int* bottom, int* right) const;
		float brightness() const;
		void brightness(float) const;
		void* data(const std::string name) const;
		int displayIndex() const;
		unsigned int flags() const;
		
		static Window* GetFromID(unsigned int id);
		
		unsigned int ID() const;
		void maximumSize(int* w, int* h) const;
		void maxSize(int* w, int* h) const
		{ maximumSize(w, h); }
		
		void minimumSize(int* w, int* h) const;
		void minSize(int* w, int* h) const
		{ minimumSize(w, h); }
		float opacity() const;
		unsigned int pixelFormat() const;
		void position(int* x, int* y) const;
		void size(int* w, int* h) const;
		std::string title() const;
		
		
		
		
	};
}