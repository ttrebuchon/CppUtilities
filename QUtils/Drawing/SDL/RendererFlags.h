#pragma once


namespace QUtils::Drawing::SDL
{
	enum struct RendererFlags
	{
		Software = 1,
		Accelerated = 2,
		PresentVsync = 4,
		TargetTexture = 8,
	};
	
	inline RendererFlags operator|(RendererFlags a, RendererFlags b)
	{
		return static_cast<RendererFlags>(static_cast<int>(a) | static_cast<int>(b));
	}
	
	inline RendererFlags operator&(RendererFlags a, RendererFlags b)
	{
		return static_cast<RendererFlags>(static_cast<int>(a) & static_cast<int>(b));
	}
	
	unsigned int SDL_RawRendererFlags(RendererFlags);
	RendererFlags SDL_EnumRendererFlags(unsigned int);
}