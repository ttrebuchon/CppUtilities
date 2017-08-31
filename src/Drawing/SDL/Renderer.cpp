#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Window.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Renderer::Renderer() : Base(NULL)
	{
		
	}
	
	Renderer::Renderer(SDL_Renderer* ptr) : Base(ptr)
	{
		
	}
	
	
	
	
	
	Renderer::Renderer(Window* win, int index, RendererFlags flags) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateRenderer(**win, index, SDL_RawRendererFlags(flags)), NULL);
		setInstance(ptr, this);
	}
	
	Renderer::~Renderer()
	{
		if (ptr != NULL)
		{
			SDL_DestroyRenderer(ptr);
		}
	}
	
	
	
	
	void Renderer::drawColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* alpha) const
	{
		SDL_CHECKERROR(SDL_GetRenderDrawColor(ptr, r, g, b, alpha), 0);
	}
	
	void Renderer::setDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
	{
		SDL_CHECKERROR(SDL_SetRenderDrawColor(ptr, r, g, b, alpha), 0);
	}
	
	void Renderer::clear()
	{
		SDL_CHECKERROR(SDL_RenderClear(ptr), 0);
	}
	
	void Renderer::copy(Texture* tex, const SDL_Rect* src, const SDL_Rect* dst)
	{
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, src, dst), 0);
	}
	
	void Renderer::copy(Texture* tex, const Rect src, const Rect dst)
	{
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, (const SDL_Rect*)&src, (const SDL_Rect*)&dst), 0);
	}
	
	void Renderer::copy(Texture* tex, const Rect* src, const Rect dst)
	{
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, (const SDL_Rect*)src, (const SDL_Rect*)&dst), 0);
	}
	
	void Renderer::copy(Texture* tex, const Rect src, const Rect* dst)
	{
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, (const SDL_Rect*)&src, (const SDL_Rect*)dst), 0);
	}
	
	void Renderer::copy(Texture* tex, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
	{
		SDL_Rect src = { sx, sy, sw, sh };
		SDL_Rect dst = { dx, dy, dw, dh };
		this->copy(tex, &src, &dst);
	}
	
	void Renderer::copy(Texture* tex)
	{
		copy(tex, NULL, NULL);
	}
	
	void Renderer::copyEx(Texture* tex, const SDL_Rect* src, const SDL_Rect* dst, const double angle, const SDL_Point* center, RendererFlip flip)
	{
		SDL_CHECKERROR(SDL_RenderCopyEx(ptr, **tex, src, dst, angle, center, (SDL_RendererFlip)SDL_RawRendererFlip(flip)), 0);
	}
	
	void Renderer::copy(Texture* tex, const Rect* src, const Rect* dst, const double angle, const Point* center, RendererFlip flip)
	{
		SDL_CHECKERROR(SDL_RenderCopyEx(ptr, **tex, (const SDL_Rect*)src, (const SDL_Rect*)dst, angle, (const SDL_Point*)center, (SDL_RendererFlip)SDL_RawRendererFlip(flip)), 0);
	}
	
	void Renderer::drawLine(int x1, int y1, int x2, int y2)
	{
		SDL_CHECKERROR(SDL_RenderDrawLine(ptr, x1, y1, x2, y2), 0);
	}
	
	void Renderer::drawLine(const Point p1, const Point p2)
	{
		SDL_CHECKERROR(SDL_RenderDrawLine(ptr, p1.x, p1.y, p2.x, p2.y), 0);
	}
	
	void Renderer::drawLines(const SDL_Point* points, int count)
	{
		SDL_CHECKERROR(SDL_RenderDrawLines(ptr, points, count), 0);
	}
	
	void Renderer::drawPoint(int x, int y)
	{
		SDL_CHECKERROR(SDL_RenderDrawPoint(ptr, x, y), 0);
	}
	
	void Renderer::drawPoints(const SDL_Point* points, int count)
	{
		SDL_CHECKERROR(SDL_RenderDrawPoints(ptr, points, count), 0);
	}
	
	void Renderer::drawRect(const SDL_Rect* rect)
	{
		SDL_CHECKERROR(SDL_RenderDrawRect(ptr, rect), 0);
	}
	
	void Renderer::drawRect(int x, int y, int w, int h)
	{
		
		SDL_Rect rect = { x, y, w, h };
		drawRect(&rect);
	}
	
	void Renderer::drawRects(const SDL_Rect* rects, int count)
	{
		SDL_CHECKERROR(SDL_RenderDrawRects(ptr, rects, count), 0);
	}
	
	void Renderer::fillRect(const SDL_Rect* rect)
	{
		SDL_CHECKERROR(SDL_RenderFillRect(ptr, rect), 0);
	}
	
	void Renderer::fillRect(const Rect rect)
	{
		this->fillRect((const SDL_Rect*)&rect);
	}
	
	void Renderer::fillRect(int x, int y, int w, int h)
	{
		SDL_Rect rect = { x, y, w, h };
		fillRect(&rect);
	}
	
	void Renderer::fillRects(const SDL_Rect* rects, int count)
	{
		SDL_CHECKERROR(SDL_RenderFillRects(ptr, rects, count), 0);
	}
	
	Texture* Renderer::target() const
	{
		auto target = SDL_GetRenderTarget(ptr);
		return Texture::getObject(target);
	}
	
	void Renderer::target(Texture* tex)
	{
		SDL_Texture* SDLPtr = NULL;
		if (tex != NULL)
		{
			SDLPtr = **tex;
		}
		SDL_CHECKERROR(SDL_SetRenderTarget(ptr, SDLPtr), 0);
	}
	
	void Renderer::scale(float* x, float* y) const
	{
		SDL_RenderGetScale(ptr, x, y);
	}
	
	void Renderer::setScale(float x, float y)
	{
		SDL_RenderSetScale(ptr, x, y);
	}
	
	void Renderer::logicalSize(int* w, int* h) const
	{
		SDL_RenderGetLogicalSize(ptr, w, h);
	}
	
	void Renderer::setLogicalSize(int w, int h)
	{
		SDL_RenderSetLogicalSize(ptr, w, h);
	}
	
	bool Renderer::integerScale() const
	{
		throw NotAvail();
		//return SDL_RenderGetIntegerScale(ptr) == SDL_TRUE;
	}
	
	void Renderer::integerScale(bool value)
	{
		throw NotAvail();
		//SDL_RenderSetIntegerScale(ptr, (value ? SDL_TRUE : SDL_FALSE));
	}
	
	void Renderer::viewport(SDL_Rect* rect) const
	{
		SDL_RenderGetViewport(ptr, rect);
	}
	
	void Renderer::viewport(int* x, int* y, int* w, int* h) const
	{
		SDL_Rect rect;
		SDL_RenderGetViewport(ptr, &rect);
		if (x != NULL)
		{
			*x = rect.x;
		}
		if (y != NULL)
		{
			*y = rect.y;
		}
		if (w != NULL)
		{
			*w = rect.w;
		}
		if (h != NULL)
		{
			*h = rect.h;
		}
	}
	
	void Renderer::setViewport(const SDL_Rect* rect)
	{
		SDL_CHECKERROR(SDL_RenderSetViewport(ptr, rect), 0);
	}
	
	void Renderer::setViewport(int x, int y, int w, int h)
	{
		SDL_Rect rect = { x, y, w, h };
		SDL_CHECKERROR(SDL_RenderSetViewport(ptr, &rect), 0);
	}
	
	void Renderer::resetViewport()
	{
		setViewport(NULL);
	}
	
	bool Renderer::targetSupported() const
	{
		return SDL_RenderTargetSupported(ptr) == SDL_TRUE;
	}
	
	BlendMode Renderer::blendMode() const
	{
		SDL_BlendMode mode;
		SDL_CHECKERROR(SDL_GetRenderDrawBlendMode(ptr, &mode), 0);
		return SDL_EnumBlendMode(mode);
	}
	
	void Renderer::blendMode(BlendMode eMode)
	{
		SDL_BlendMode mode = (SDL_BlendMode)SDL_RawBlendMode(eMode);
		SDL_CHECKERROR(SDL_SetRenderDrawBlendMode(ptr, mode), 0);
	}
	
	void Renderer::renderPresent()
	{
		SDL_RenderPresent(ptr);
	}
	
	void Renderer::readPixels(const SDL_Rect* area, PixelFormat format, void* pixels, int rowLen) const
	{
		SDL_CHECKERROR(SDL_RenderReadPixels(ptr, area, SDL_RawPixelFormat(format), pixels, rowLen), 0);
	}
	
	void Renderer::readPixels(const Rect* area, PixelFormat format, void* pixels, int rowLen) const
	{
		SDL_CHECKERROR(SDL_RenderReadPixels(ptr, (const SDL_Rect*)area, SDL_RawPixelFormat(format), pixels, rowLen), 0);
	}
}