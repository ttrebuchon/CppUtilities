#pragma once
#include "SDLObject.h"
#include "BlendMode.h"
#include "RendererFlags.h"
#include "Rect.h"
#include "Point.h"
#include "RendererFlip.h"
#include "PixelFormat.h"


class SDL_Renderer;
struct SDL_Rect;
struct SDL_Point;


namespace QUtils::Drawing::SDL
{
	class Texture;
	class Window;
	
	class Renderer : public Internal::SDLObject<SDL_Renderer, Renderer>
	{
		typedef Internal::SDLObject<SDL_Renderer, Renderer> Base;
		friend Base;
		
		protected:
		Renderer();
		Renderer(SDL_Renderer*);
		
		
		public:
		Renderer(Window*, int index, RendererFlags);
		
		virtual ~Renderer();
		
		BlendMode blendMode() const;
		void blendMode(BlendMode);
		
		
		
		void clear();
		
		Rect clipRect() const;
		void clipRect(Rect*) const;
		void clipRect(SDL_Rect*) const;
		void clipRect(const Rect&);
		
		
		void copy(Texture*, const SDL_Rect* src, const SDL_Rect* dst);
		void copy(Texture*, const Rect src, const Rect dst);
		void copy(Texture*, const Rect* src, const Rect dst);
		void copy(Texture*, const Rect src, const Rect* dst);
		void copy(Texture*, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);
		void copy(Texture*);
		
		void copyEx(Texture*, const SDL_Rect* src, const SDL_Rect* dst, const double angle, const SDL_Point* center, RendererFlip flip);
		void copy(Texture*, const Rect* src, const Rect* dst, const double angle, const Point* center, RendererFlip flip);
		inline void copy(Texture* tex, const SDL_Rect* src, const SDL_Rect* dst, const double angle, const SDL_Point* center, RendererFlip flip)
		{
			copyEx(tex, src, dst, angle, center, flip);
		}
		inline void copy(Texture* tex, const Rect src, const Rect dst, const double angle, const Point center, RendererFlip flip = RendererFlip::None)
		{
			copy(tex, &src, &dst, angle, &center, flip);
		}
		inline void copy(Texture* tex, const Rect* src, const Rect dst, const double angle, const Point center, RendererFlip flip = RendererFlip::None)
		{
			copy(tex, src, &dst, angle, &center, flip);
		}
		inline void copy(Texture* tex, const Rect src, const Rect* dst, const double angle, const Point center, RendererFlip flip = RendererFlip::None)
		{
			copy(tex, &src, dst, angle, &center, flip);
		}
		
		inline void copy(Texture* tex, const Rect src, const Rect dst, const double angle, const Point* center = NULL, RendererFlip flip = RendererFlip::None)
		{
			copy(tex, &src, &dst, angle, center, flip);
		}
		void copy(Texture* tex, const Rect* src, const Rect dst, const double angle, const Point* center = NULL, RendererFlip flip = RendererFlip::None)
		{
			copy(tex, src, &dst, angle, center, flip);
		}
		inline void copy(Texture* tex, const Rect src, const Rect* dst, const double angle, const Point* center = NULL, RendererFlip flip = RendererFlip::None)
		{
			copy(tex, &src, dst, angle, center, flip);
		}
		
		void drawColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* alpha) const;
		
		void setDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
		
		
		void drawLine(int x1, int y1, int x2, int y2);
		void drawLine(const Point p1, const Point p2);
		void drawLines(const SDL_Point*, int count);
		void drawPoint(int x, int y);
		void drawPoints(const SDL_Point*, int count);
		void drawRect(const SDL_Rect*);
		void drawRect(int x, int y, int w, int h);
		void drawRects(const SDL_Rect*, int count);
		void fillRect(const SDL_Rect*);
		void fillRect(const Rect);
		void fillRect(int x, int y, int w, int h);
		void fillRects(const SDL_Rect*, int count);
		
		bool integerScale() const;
		void integerScale(bool);
		
		bool isClipEnabled() const;
		
		void logicalSize(int* w, int* h) const;
		void setLogicalSize(int w, int h);
		
		void renderPresent();
		void readPixels(const SDL_Rect*, PixelFormat, void*, int) const;
		void readPixels(const Rect*, PixelFormat, void*, int) const;
		inline void readPixels(const Rect area, PixelFormat format, void* pixels, int rowLen) const
		{
			readPixels(&area, format, pixels, rowLen);
		}
		
		void scale(float* x, float* y) const;
		void setScale(float x, float y);
		Texture* target() const;
		void target(Texture*);
		
		
		bool targetSupported() const;
		
		
		
		void viewport(SDL_Rect*) const;
		void viewport(int* x, int* y, int* w, int* h) const;
		void setViewport(const SDL_Rect*);
		void setViewport(int x, int y, int w, int h);
		void resetViewport();
		
	};
}