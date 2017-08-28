#pragma once
#include "SDLObject.h"
#include "PixelFormat.h"
#include "Rect.h"


class SDL_Surface;
struct SDL_Rect;
struct SDL_PixelFormat;

namespace QUtils::Drawing::SDL
{
	class Texture;
	class Renderer;
	
	class Surface : public Internal::SDLObject<SDL_Surface, Surface>
	{
		typedef Internal::SDLObject<SDL_Surface, Surface> Base;
		friend Base;
		friend class Window;
		protected:
		bool windowSurface;
		Surface();
		Surface(SDL_Surface*);
		
		void setWindowSurface(bool);
		
		public:
		Surface(int w, int h, int depth, unsigned int Rmask, unsigned int Gmask, unsigned int Bmask, unsigned int Amask);
		Surface(int w, int h, PixelFormat);
		
		
		virtual ~Surface();
		
		
		Texture* createTexture(Renderer*) const;
		Renderer* createSoftwareRenderer() const;
		inline Renderer* softRenderer() const
		{
			return createSoftwareRenderer();
		}
		const SDL_PixelFormat* format() const;
		int width() const;
		int height() const;
		int pitch() const;
		inline int w() const
		{ return width(); }
		inline int h() const
		{ return height(); }
		void*& pixels();
		const void* pixels() const;
		void*& userdata();
		const void* userdata() const;
		int& refcount();
		const int& refcount() const;
		SDL_Rect* clip_rect();
		const SDL_Rect* clip_rect() const;
		void setRLE(bool);
		void lock();
		void unlock();
		bool mustLock() const;
		
		void blitTo(Surface*, const SDL_Rect* src, SDL_Rect* dst) const;
		void blitToScaled(Surface*, const SDL_Rect* src, SDL_Rect* dst) const;
		void blitTo(Surface*, const Rect* src, Rect* dst) const;
		void blitToScaled(Surface*, const Rect* src, Rect* dst) const;
		
		inline void blitTo(Surface* surf, const Rect src, Rect dst) const
		{
			blitTo(surf, &src, &dst);
		}
		inline void blitToScaled(Surface* surf, const Rect src, Rect dst) const
		{
			blitToScaled(surf, &src, &dst);
		}
		inline void blitTo(Surface* surf, const Rect* src, Rect dst) const
		{
			blitTo(surf, src, &dst);
		}
		inline void blitToScaled(Surface* surf, const Rect* src, Rect dst) const
		{
			blitToScaled(surf, src, &dst);
		}
		inline void blitTo(Surface* surf, const Rect src, Rect* dst) const
		{
			blitTo(surf, &src, dst);
		}
		inline void blitToScaled(Surface* surf, const Rect src, Rect* dst) const
		{
			blitToScaled(surf, &src, dst);
		}
		
	};
}