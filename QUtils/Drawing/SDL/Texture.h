#pragma once
#include "SDLObject.h"
#include "TextureAccess.h"
#include "Color.h"
#include "BlendMode.h"
#include "Rect.h"
#include "PixelFormat.h"

class SDL_Texture;
struct SDL_Rect;


namespace QUtils::Drawing::SDL
{
	class Renderer;
	class Surface;
	
	class Texture : public Internal::SDLObject<SDL_Texture, Texture>
	{
		typedef Internal::SDLObject<SDL_Texture, Texture> Base;
		friend Base;
		protected:
		Texture();
		Texture(SDL_Texture*);
		
		public:
		Texture(Renderer*, PixelFormat format, TextureAccess, int w, int h);
		Texture(Renderer*, Surface*);
		
		
		virtual ~Texture();
		
		unsigned char alphaMod() const;
		void alphaMod(unsigned char);
		void colorMod(unsigned char* r, unsigned char* g, unsigned char* b) const;
		void colorMod(unsigned char r, unsigned char g, unsigned char b);
		Color colorMod() const;
		void colorMod(const Color);
		BlendMode blendMode() const;
		void blendMode(BlendMode);
		void query(PixelFormat*, TextureAccess*, int* w, int* h) const;
		void size(int* w, int* h) const;
		int width() const;
		int height() const;
		void lock(const SDL_Rect* area, void** pixels, int* rowLen);
		void lock(void** pixels, int* rowLen);
		void lock(const Rect* area, void** pixels, int* rowLen);
		void unlock();
		void update(const SDL_Rect* area, const void* pixels, int rowLen);
	};
}