#pragma once
#include "SDLObject.h"
#include "TextureAccess.h"
#include "Color.h"
#include "BlendMode.h"

class SDL_Texture;


namespace QUtils::Drawing::SDL
{
	class Renderer;
	
	class Texture : public Internal::SDLObject<SDL_Texture, Texture>
	{
		typedef Internal::SDLObject<SDL_Texture, Texture> Base;
		friend Base;
		protected:
		Texture();
		Texture(SDL_Texture*);
		
		public:
		Texture(Renderer*, unsigned int format, TextureAccess, int w, int h); 
		
		
		virtual ~Texture();
		
		unsigned char alphaMod() const;
		void alphaMod(unsigned char);
		void colorMod(unsigned char* r, unsigned char* g, unsigned char* b) const;
		void colorMod(unsigned char r, unsigned char g, unsigned char b);
		Color colorMod() const;
		void colorMod(const Color);
		BlendMode blendMode() const;
		void blendMode(BlendMode);
		
	};
}