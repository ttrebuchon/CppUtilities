#include <QUtils/Drawing/SDL/Texture.h>
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
	
	Texture::~Texture()
	{
		if (ptr != NULL)
		{
			SDL_DestroyTexture(ptr);
		}
	}
	
	
	
}