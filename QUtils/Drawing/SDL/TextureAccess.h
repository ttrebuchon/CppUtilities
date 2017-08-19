#pragma once

namespace QUtils::Drawing::SDL
{
	enum TextureAccess
	{
		Static = 1,
		Streaming = 2,
		Target = 4,
	};
	
	int SDL_RawTextureAccess(TextureAccess);
	TextureAccess SDL_EnumTextureAccess(int);
	
	
}