#pragma once


namespace QUtils::Drawing::SDL
{
	enum struct FontStyle : int
	{
		Normal = 1,
		Bold = 2,
		Italic = 4,
		Underline = 8,
		Strikethrough = 16,
	};
	
	inline FontStyle operator|(FontStyle a, FontStyle b)
	{
		return static_cast<FontStyle>(static_cast<int>(a) | static_cast<int>(b));
	}
	
	inline FontStyle operator&(FontStyle a, FontStyle b)
	{
		return static_cast<FontStyle>(static_cast<int>(a) & static_cast<int>(b));
	}
	
	int SDL_RawFontStyle(FontStyle);
	FontStyle SDL_EnumFontStyle(int);
}