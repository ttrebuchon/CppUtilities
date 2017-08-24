#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Texture::Texture() : Base(NULL)
	{
		
	}
	
	Texture::Texture(SDL_Texture* ptr) : Base(ptr)
	{
		
	}
	
	
	
	
	
	
	Texture::Texture(Renderer* ren, PixelFormat pixelFormat, TextureAccess access, int w, int h) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateTexture(**ren, SDL_RawPixelFormat(pixelFormat), SDL_RawTextureAccess(access), w, h), NULL);
		setInstance(ptr, this);
	}
	
	Texture::Texture(Renderer* ren, Surface* surf) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateTextureFromSurface(**ren, **surf), NULL);
		setInstance(ptr, this);
	}
	
	Texture::~Texture()
	{
		if (ptr != NULL)
		{
			SDL_DestroyTexture(ptr);
		}
	}
	
	
	
	unsigned char Texture::alphaMod() const
	{
		unsigned char value;
		SDL_CHECKERROR(SDL_GetTextureAlphaMod(ptr, &value), 0);
		return value;
	}
	
	void Texture::alphaMod(unsigned char value)
	{
		SDL_CHECKERROR(SDL_SetTextureAlphaMod(ptr, value), 0);
	}
	
	void Texture::colorMod(unsigned char* r, unsigned char* g, unsigned char* b) const
	{
		SDL_CHECKERROR(SDL_GetTextureColorMod(ptr, r, g, b), 0);
	}
	
	void Texture::colorMod(unsigned char r, unsigned char g, unsigned char b)
	{
		SDL_CHECKERROR(SDL_SetTextureColorMod(ptr, r, g, b), 0);
	}
	
	Color Texture::colorMod() const
	{
		Color col;
		SDL_CHECKERROR(SDL_GetTextureColorMod(ptr, &col.r, &col.g, &col.b), 0);
		return col;
	}
	
	void Texture::colorMod(const Color col)
	{
		SDL_CHECKERROR(SDL_SetTextureColorMod(ptr, col.r, col.g, col.b), 0);
	}
	
	BlendMode Texture::blendMode() const
	{
		SDL_BlendMode mode;
		SDL_CHECKERROR(SDL_GetTextureBlendMode(ptr, &mode), 0);
		return SDL_EnumBlendMode(mode);
	}
	
	void Texture::blendMode(BlendMode eMode)
	{
		SDL_BlendMode mode = (SDL_BlendMode)SDL_RawBlendMode(eMode);
		SDL_CHECKERROR(SDL_SetTextureBlendMode(ptr, mode), 0);
	}
	
	void Texture::query(PixelFormat* format, TextureAccess* access, int* w, int* h) const
	{
		SDL_CHECKERROR(SDL_QueryTexture(ptr, (unsigned int*)format, (int*)access, w, h), 0);
	}
	
	void Texture::size(int* w, int* h) const
	{
		SDL_CHECKERROR(SDL_QueryTexture(ptr, NULL, NULL, w, h), 0);
	}
	
	int Texture::width() const
	{
		int w;
		SDL_CHECKERROR(SDL_QueryTexture(ptr, NULL, NULL, &w, NULL), 0);
		return w;
	}
	
	int Texture::height() const
	{
		int h;
		SDL_CHECKERROR(SDL_QueryTexture(ptr, NULL, NULL, NULL, &h), 0);
		return h;
	}
	
	void Texture::lock(const SDL_Rect* area, void** pixels, int* rowLen)
	{
		SDL_CHECKERROR(SDL_LockTexture(ptr, area, pixels, rowLen), 0);
	}
	
	void Texture::lock(void** pixels, int* rowLen)
	{
		SDL_CHECKERROR(SDL_LockTexture(ptr, NULL, pixels, rowLen), 0);
	}
	
	void Texture::lock(const Rect* area, void** pixels, int* rowLen)
	{
		SDL_CHECKERROR(SDL_LockTexture(ptr, (const SDL_Rect*)area, pixels, rowLen), 0);
	}
	
	void Texture::unlock()
	{
		SDL_UnlockTexture(ptr);
	}
	
	void Texture::update(const SDL_Rect* area, const void* pixels, int rowLen)
	{
		SDL_CHECKERROR(SDL_UpdateTexture(ptr, area, pixels, rowLen), 0);
	}
	
	
	
}