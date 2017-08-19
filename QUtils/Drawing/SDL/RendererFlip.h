#pragma once


namespace QUtils::Drawing::SDL
{
	enum RendererFlip
	{
		NoFlip = 1,
		Horizontal = 2,
		Vertical = 4,
	};
	
	inline RendererFlip operator|(RendererFlip a, RendererFlip b)
	{
		return static_cast<RendererFlip>(static_cast<int>(a) | static_cast<int>(b));
	}
	
	inline RendererFlip operator&(RendererFlip a, RendererFlip b)
	{
		return static_cast<RendererFlip>(static_cast<int>(a) & static_cast<int>(b));
	}
	
	unsigned int SDL_RawRendererFlip(RendererFlip);
	RendererFlip SDL_EnumRendererFlip(unsigned int);
}