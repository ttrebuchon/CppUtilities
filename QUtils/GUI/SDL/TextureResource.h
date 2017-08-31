#pragma once

#include "../Resource.h"
#include "SurfaceResource.h"

namespace QUtils::Drawing::SDL
{
	class Texture;
	class Renderer;
}


namespace QUtils::GUI
{
class AppWindow;
namespace SDL
{
	class SDLAppWindow;
	
	class SDLTextureResourceLoader : public ResourceLoader<Drawing::SDL::Texture, Drawing::SDL::Renderer*>
	{
		private:
		typedef ResourceLoader<Drawing::SDL::Texture, Drawing::SDL::Renderer*> Base;
		typedef Resource<Drawing::SDL::Texture, Drawing::SDL::Renderer*> TextureResource;
		
		protected:
		Drawing::SDL::Texture* texture;
		Drawing::SDL::Renderer* renderer;
		
		TextureResource* load(Drawing::SDL::Renderer* renderer)
		{
			throw std::exception();
		}
		
		public:
		SDLTextureResourceLoader(const std::string name) : Base(name)
		{}
		
	};
	
}
}