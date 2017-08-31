#pragma once

#include "../Resource.h"

#include <QUtils/Drawing/SDL/Font.h>

namespace QUtils
{
namespace Drawing::SDL
{
	class Font;
}
namespace GUI::SDL
{
	class SDLFontResourceLoader : public ResourceLoader<Drawing::SDL::Font, int>
	{
		private:
		
		
		
		public:
		
	};
	
	class SDLFontFileResourceLoader : public ResourceLoader<Drawing::SDL::Font, int>
	{
		private:
		typedef ResourceLoader<Drawing::SDL::Font, int> Base;
		typedef Resource<Drawing::SDL::Font, int> FontResource;
		
		
		protected:
		std::string filepath;
		
		virtual FontResource* load(int fontsize)
		{
			return new FontResource(name, std::shared_ptr<Drawing::SDL::Font>(Drawing::SDL::Font::Open(filepath, fontsize)));
		}
		
		
		public:
		SDLFontFileResourceLoader(const std::string name, const std::string filepath) : Base(name), filepath(filepath)
		{}
		
	};
}
}