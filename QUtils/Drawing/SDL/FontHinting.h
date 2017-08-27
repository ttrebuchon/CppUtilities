#pragma once

namespace QUtils::Drawing::SDL
{
	enum struct FontHinting
	{
		Normal = 1,
		Light = 2,
		Mono = 3,
		None = 4,
	};
	
	int SDL_RawFontHinting(FontHinting);
	FontHinting SDL_EnumFontHinting(int);
	
	
}