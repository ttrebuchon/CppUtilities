#pragma once
#include "SDLObject.h"
#include "BlendMode.h"
#include "RendererFlags.h"


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
		
		void drawColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* alpha) const;
		
		void setDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
		
		void clear();
		void copy(Texture*, const SDL_Rect* src, const SDL_Rect* dst);
		void copy(Texture*, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);
		void copy(Texture*);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawLines(const SDL_Point*, int count);
		void drawPoint(int x, int y);
		void drawPoints(const SDL_Point*, int count);
		void drawRect(const SDL_Rect*);
		void drawRect(int x, int y, int w, int h);
		void drawRects(const SDL_Rect*, int count);
		void fillRect(const SDL_Rect*);
		void fillRect(int x, int y, int w, int h);
		void fillRects(const SDL_Rect*, int count);
		
		Texture* target() const;
		void target(Texture*);
		
		void scale(float* x, float* y) const;
		void setScale(float x, float y);
		void logicalSize(int* w, int* h) const;
		void setLogicalSize(int w, int h);
		bool integerScale() const;
		void integerScale(bool);
		
		void viewport(SDL_Rect*) const;
		void viewport(int* x, int* y, int* w, int* h) const;
		void setViewport(const SDL_Rect*);
		void setViewport(int x, int y, int w, int h);
		void resetViewport();
		bool targetSupported() const;
		BlendMode blendMode() const;
		void blendMode(BlendMode);
	};
}