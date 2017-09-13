#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Window.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/Version.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Renderer::Renderer() : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	Renderer::Renderer(SDL_Renderer* ptr) : Base(ptr)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	
	Renderer::Renderer(Window* win, int index, RendererFlags flags) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ERRORIF(ptr = SDL_CreateRenderer(**win, index, SDL_RawRendererFlags(flags)), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Renderer::~Renderer()
	{
		#ifdef QUTILS_HAS_SDL2
		if (ptr != NULL)
		{
			SDL_DestroyRenderer(ptr);
		}
		#endif
	}
	
	
	
	
	void Renderer::drawColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_GetRenderDrawColor(ptr, r, g, b, alpha), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_SetRenderDrawColor(ptr, r, g, b, alpha), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::clear()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderClear(ptr), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	#if QUTILS_SDL_VERSION_HIDE(2,0,4)
	Rect Renderer::getClipRect() const
	{
		#if SDL_VERSION_MIN(2,0,4)
		SDL_Rect r;
		SDL_RenderGetClipRect(ptr, &r);
		return { r.x, r.y, r.w, r.h };
		#else
		throw NotAvail();
		#endif
	}
	
	
	void Renderer::clipRect(Rect* r) const
	{
		#if SDL_VERSION_MIN(2,0,4)
		SDL_RenderGetClipRect(ptr, (SDL_Rect*)r);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::clipRect(SDL_Rect* r) const
	{
		#if SDL_VERSION_MIN(2,0,4)
		SDL_RenderGetClipRect(ptr, r);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setClipRect(const Rect& r)
	{
		#if SDL_VERSION_MIN(2,0,4)
		SDL_RenderSetClipRect(ptr, (const SDL_Rect*)&r);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setClipRect(const Rect* r)
	{
		#if SDL_VERSION_MIN(2,0,4)
		SDL_RenderSetClipRect(ptr, (const SDL_Rect*)r);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setClipRect(const SDL_Rect* r)
	{
		#if SDL_VERSION_MIN(2,0,4)
		SDL_RenderSetClipRect(ptr, r);
		#else
		throw NotAvail();
		#endif
	}
	#endif
	
	void Renderer::copy(Texture* tex, const SDL_Rect* src, const SDL_Rect* dst)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, src, dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copy(Texture* tex, const Rect src, const Rect dst)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, (const SDL_Rect*)&src, (const SDL_Rect*)&dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copy(Texture* tex, const Rect* src, const Rect dst)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, (const SDL_Rect*)src, (const SDL_Rect*)&dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copy(Texture* tex, const Rect src, const Rect* dst)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderCopy(ptr, **tex, (const SDL_Rect*)&src, (const SDL_Rect*)dst), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copy(Texture* tex, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Rect src = { sx, sy, sw, sh };
		SDL_Rect dst = { dx, dy, dw, dh };
		this->copy(tex, &src, &dst);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copy(Texture* tex)
	{
		#ifdef QUTILS_HAS_SDL2
		copy(tex, NULL, NULL);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copyEx(Texture* tex, const SDL_Rect* src, const SDL_Rect* dst, const double angle, const SDL_Point* center, RendererFlip flip)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderCopyEx(ptr, **tex, src, dst, angle, center, (SDL_RendererFlip)SDL_RawRendererFlip(flip)), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::copy(Texture* tex, const Rect* src, const Rect* dst, const double angle, const Point* center, RendererFlip flip)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderCopyEx(ptr, **tex, (const SDL_Rect*)src, (const SDL_Rect*)dst, angle, (const SDL_Point*)center, (SDL_RendererFlip)SDL_RawRendererFlip(flip)), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawLine(int x1, int y1, int x2, int y2)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawLine(ptr, x1, y1, x2, y2), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawLine(const Point p1, const Point p2)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawLine(ptr, p1.x, p1.y, p2.x, p2.y), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawLines(const SDL_Point* points, int count)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawLines(ptr, points, count), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawPoint(int x, int y)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawPoint(ptr, x, y), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawPoints(const SDL_Point* points, int count)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawPoints(ptr, points, count), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawRect(const SDL_Rect* rect)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawRect(ptr, rect), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawRect(int x, int y, int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		
		SDL_Rect rect = { x, y, w, h };
		drawRect(&rect);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::drawRects(const SDL_Rect* rects, int count)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderDrawRects(ptr, rects, count), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::fillRect(const SDL_Rect* rect)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderFillRect(ptr, rect), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::fillRect(const Rect rect)
	{
		#ifdef QUTILS_HAS_SDL2
		this->fillRect((const SDL_Rect*)&rect);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::fillRect(int x, int y, int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Rect rect = { x, y, w, h };
		fillRect(&rect);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::fillRects(const SDL_Rect* rects, int count)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderFillRects(ptr, rects, count), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	Texture* Renderer::target() const
	{
		#ifdef QUTILS_HAS_SDL2
		auto target = SDL_GetRenderTarget(ptr);
		return Texture::getObject(target);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::target(Texture* tex)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Texture* SDLPtr = NULL;
		if (tex != NULL)
		{
			SDLPtr = **tex;
		}
		SDL_CHECKERROR(SDL_SetRenderTarget(ptr, SDLPtr), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::scale(float* x, float* y) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RenderGetScale(ptr, x, y);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setScale(float x, float y)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RenderSetScale(ptr, x, y);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::logicalSize(int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RenderGetLogicalSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setLogicalSize(int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RenderSetLogicalSize(ptr, w, h);
		#else
		throw NotAvail();
		#endif
	}
	
	#if QUTILS_SDL_VERSION_HIDE(2,0,5)
	bool Renderer::integerScale() const
	{
		#if SDL_VERSION_MIN(2,0,5)
		return SDL_RenderGetIntegerScale(ptr) == SDL_TRUE;
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::integerScale(bool value)
	{
		#if SDL_VERSION_MIN(2, 0, 5)
		SDL_RenderSetIntegerScale(ptr, (value ? SDL_TRUE : SDL_FALSE));
		#else
		throw NotAvail();
		#endif
	}
	
	#endif
	
	#if QUTILS_SDL_VERSION_HIDE(2,0,4)
	bool Renderer::isClipEnabled() const
	{
		#if SDL_VERSION_MIN(2,0,4)
		return SDL_RenderIsClipEnabled(ptr) == SDL_TRUE;
		#else
		throw NotAvail();
		#endif
	}
	#endif
	
	void Renderer::viewport(SDL_Rect* rect) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RenderGetViewport(ptr, rect);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::viewport(int* x, int* y, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
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
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setViewport(const SDL_Rect* rect)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderSetViewport(ptr, rect), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::setViewport(int x, int y, int w, int h)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Rect rect = { x, y, w, h };
		SDL_CHECKERROR(SDL_RenderSetViewport(ptr, &rect), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::resetViewport()
	{
		#ifdef QUTILS_HAS_SDL2
		setViewport(NULL);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Renderer::targetSupported() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_RenderTargetSupported(ptr) == SDL_TRUE;
		#else
		throw NotAvail();
		#endif
	}
	
	BlendMode Renderer::blendMode() const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_BlendMode mode;
		SDL_CHECKERROR(SDL_GetRenderDrawBlendMode(ptr, &mode), 0);
		return SDL_EnumBlendMode(mode);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::blendMode(BlendMode eMode)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_BlendMode mode = (SDL_BlendMode)SDL_RawBlendMode(eMode);
		SDL_CHECKERROR(SDL_SetRenderDrawBlendMode(ptr, mode), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::renderPresent()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_RenderPresent(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::readPixels(const SDL_Rect* area, PixelFormat format, void* pixels, int rowLen) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderReadPixels(ptr, area, SDL_RawPixelFormat(format), pixels, rowLen), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Renderer::readPixels(const Rect* area, PixelFormat format, void* pixels, int rowLen) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RenderReadPixels(ptr, (const SDL_Rect*)area, SDL_RawPixelFormat(format), pixels, rowLen), 0);
		#else
		throw NotAvail();
		#endif
	}
}