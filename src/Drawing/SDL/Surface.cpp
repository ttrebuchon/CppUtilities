#include <QUtils/Drawing/SDL/Surface.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Texture.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	Surface::Surface() : Base(NULL)
	{
		
	}
	
	
	
	
	Surface::Surface(SDL_Surface* ptr) : Base(ptr)
	{
		
	}
	
	Surface::~Surface()
	{
		if (ptr != NULL)
		{
			SDL_FreeSurface(ptr);
		}
	}
	
	
	
	
	Texture* Surface::createTexture(Renderer* ren) const
	{
		SDL_Texture* texPtr;
		SDL_ERRORIF(texPtr = SDL_CreateTextureFromSurface(**ren, ptr), NULL);
		return Texture::getObject(texPtr);
	}
}