#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Renderer.h>
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
	
	
	
	
	
	
	Texture::Texture(Renderer* ren, unsigned int pixelFormat, TextureAccess access, int w, int h) : Base(NULL)
	{
		SDL_ERRORIF(ptr = SDL_CreateTexture(**ren, pixelFormat, SDL_RawTextureAccess(access), w, h), NULL);
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
	
	
	
}