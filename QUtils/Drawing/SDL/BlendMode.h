#pragma once

namespace QUtils::Drawing::SDL
{
	enum struct BlendMode
	{
		None = 1,
		Blend = 2,
		Add = 4,
		Mod = 8,
	};
	
	int SDL_RawBlendMode(BlendMode);
	BlendMode SDL_EnumBlendMode(int);
	
	
}