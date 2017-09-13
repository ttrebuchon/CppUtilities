#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Texture::Texture() : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	Texture::Texture(SDL_Texture* ptr) : Base(ptr)
	{
		#ifdef QUTILS_HAS_SDL2
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	
	
	Texture::Texture(Renderer* ren, PixelFormat pixelFormat, TextureAccess access, int w, int h) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ERRORIF(ptr = SDL_CreateTexture(**ren, SDL_RawPixelFormat(pixelFormat), SDL_RawTextureAccess(access), w, h), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Texture::Texture(Renderer* ren, Surface* surf) : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_ERRORIF(ptr = SDL_CreateTextureFromSurface(**ren, **surf), NULL);
		setInstance(ptr, this);
		#else
		throw NotAvail();
		#endif
	}
	
	Texture::~Texture()
	{
		#ifdef QUTILS_HAS_SDL2
		if (ptr != NULL)
		{
			SDL_DestroyTexture(ptr);
		}
		#endif
	}
	
	
	
	unsigned char Texture::alphaMod() const
	{
		#ifdef QUTILS_HAS_SDL2
		unsigned char value;
		SDL_CHECKERROR(SDL_GetTextureAlphaMod(ptr, &value), 0);
		return value;
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::alphaMod(unsigned char value)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_SetTextureAlphaMod(ptr, value), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::colorMod(unsigned char* r, unsigned char* g, unsigned char* b) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_GetTextureColorMod(ptr, r, g, b), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::colorMod(unsigned char r, unsigned char g, unsigned char b)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_SetTextureColorMod(ptr, r, g, b), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	Color Texture::colorMod() const
	{
		#ifdef QUTILS_HAS_SDL2
		Color col;
		SDL_CHECKERROR(SDL_GetTextureColorMod(ptr, &col.r, &col.g, &col.b), 0);
		return col;
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::colorMod(const Color col)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_SetTextureColorMod(ptr, col.r, col.g, col.b), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	BlendMode Texture::blendMode() const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_BlendMode mode;
		SDL_CHECKERROR(SDL_GetTextureBlendMode(ptr, &mode), 0);
		return SDL_EnumBlendMode(mode);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::blendMode(BlendMode eMode)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_BlendMode mode = (SDL_BlendMode)SDL_RawBlendMode(eMode);
		SDL_CHECKERROR(SDL_SetTextureBlendMode(ptr, mode), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::query(PixelFormat* format, TextureAccess* access, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_QueryTexture(ptr, (unsigned int*)format, (int*)access, w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::size(int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_QueryTexture(ptr, NULL, NULL, w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	int Texture::width() const
	{
		#ifdef QUTILS_HAS_SDL2
		int w;
		SDL_CHECKERROR(SDL_QueryTexture(ptr, NULL, NULL, &w, NULL), 0);
		return w;
		#else
		throw NotAvail();
		#endif
	}
	
	int Texture::height() const
	{
		#ifdef QUTILS_HAS_SDL2
		int h;
		SDL_CHECKERROR(SDL_QueryTexture(ptr, NULL, NULL, NULL, &h), 0);
		return h;
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::lock(const SDL_Rect* area, void** pixels, int* rowLen)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_LockTexture(ptr, area, pixels, rowLen), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::lock(void** pixels, int* rowLen)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_LockTexture(ptr, NULL, pixels, rowLen), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::lock(const Rect* area, void** pixels, int* rowLen)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_LockTexture(ptr, (const SDL_Rect*)area, pixels, rowLen), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::unlock()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_UnlockTexture(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Texture::update(const SDL_Rect* area, const void* pixels, int rowLen)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_UpdateTexture(ptr, area, pixels, rowLen), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	
	
}