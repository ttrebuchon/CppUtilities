#pragma once
#include <string>
#include "WindowFlags.h"
#include "SDLObject.h"
#include "Event.h"
#include "Version.h"



class SDL_Window;
struct SDL_Rect;
union SDL_Event;

namespace QUtils::Drawing::SDL
{
	class Surface;
	class Renderer;
	
	class Window : public Internal::SDLObject<SDL_Window, Window>
	{
		typedef Internal::SDLObject<SDL_Window, Window> Base;
		friend Base;
		protected:
		Window();
		Window(SDL_Window*);
		
		public:
		Window(const std::string title, int x, int y, int w, int h, WindowFlags flags);
		Window(const void* data);
		virtual ~Window();
		
		#if QUTILS_SDL_VERSION_HIDE(2,0,5)
		int bordersSize(int* top, int* left, int* bottom, int* right) const;
		#endif
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
		void setMaximumSize(int w, int h);
		void setMaxSize(int w, int h)
		{ setMaximumSize(w, h); }
		
		void setMinimumSize(int w, int h);
		void setMinSize(int w, int h)
		{ setMinimumSize(w, h); }
		float opacity() const;
		unsigned int pixelFormat() const;
		void position(int* x, int* y) const;
		void setPosition(int x, int y);
		void size(int* w, int* h) const;
		void setSize(int w, int h);
		Surface* surface() const;
		std::string title() const;
		void title(const std::string);
		bool visible() const;
		void show();
		void hide();
		void maximize();
		void minimize();
		void raise();
		void restore();
		bool fullscreen() const;
		void fullscreen(bool);
		bool fullscreenDesktop() const;
		void fullscreenDesktop(bool);
		bool grabbed() const;
		void grabbed(bool);
		void setIcon(Surface*);
		void updateSurface();
		void updateSurface(int x, int y, int w, int h);
		void updateSurfaceRects(const SDL_Rect*, int count);
		Renderer* renderer() const;
		
		int width() const;
		int height() const;
		int x() const;
		int y() const;
		
		
		
	};
}

#include "VersionUndef.h"