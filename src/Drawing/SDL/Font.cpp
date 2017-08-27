#include <QUtils/Drawing/SDL/Font.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/Surface.h>

#include "IfTTF.h"


namespace QUtils::Drawing::SDL
{
	Font::Font() : Base(NULL)
	{
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
	}
	
	Font::Font(TTF_Font* ptr) : Base(ptr)
	{
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
	}
	
	
	
	
	
	
	Font* Font::Open(const std::string file, int size)
	{
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
		TTF_Font* ptr;
		TTF_ERRORIF(ptr = TTF_OpenFont(file.c_str(), size), NULL);
		return Font::getObject(ptr);
	}
	
	Font* Font::OpenFont(const std::string file, int size)
	{
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
		TTF_Font* ptr;
		TTF_ERRORIF(ptr = TTF_OpenFont(file.c_str(), size), NULL);
		return Font::getObject(ptr);
	}
	
	
	
	
	FontStyle Font::style() const
	{
		return SDL_EnumFontStyle(TTF_GetFontStyle(ptr));
	}
	
	void Font::style(FontStyle style)
	{
		TTF_SetFontStyle(ptr, SDL_RawFontStyle(style));
	}
		
	int Font::outline() const
	{
		return TTF_GetFontOutline(ptr);
	}
	
	void Font::outline(int val)
	{
		TTF_SetFontOutline(ptr, val);
	}
		
	FontHinting Font::hinting() const
	{
		return SDL_EnumFontHinting(TTF_GetFontHinting(ptr));
	}
	
	void Font::hinting(FontHinting hinting)
	{
		TTF_SetFontHinting(ptr, SDL_RawFontHinting(hinting));
	}
		
	bool Font::kerning() const
	{
		return TTF_GetFontKerning(ptr) != 0;
	}
	
	void Font::kerning(bool val)
	{
		TTF_SetFontKerning(ptr, (int)val);
	}
		
	int Font::height() const
	{
		return TTF_FontHeight(ptr);
	}
	
	int Font::ascent() const
	{
		return TTF_FontAscent(ptr);
	}
	
	int Font::descent() const
	{
		return TTF_FontDescent(ptr);
	}
	
	int Font::lineSkip() const
	{
		return TTF_FontLineSkip(ptr);
	}
	
	long Font::faces() const
	{
		return TTF_FontFaces(ptr);
	}
	
	bool Font::fixedWidth() const
	{
		return TTF_FontFaceIsFixedWidth(ptr) > 0;
	}
	
	bool Font::isFixedWidth() const
	{
		return TTF_FontFaceIsFixedWidth(ptr) > 0;
	}
	
	std::string Font::familyName() const
	{
		return std::string(TTF_FontFaceFamilyName(ptr));
	}
	
	std::string Font::styleName() const
	{
		return std::string(TTF_FontFaceStyleName(ptr));
	}
	
	int Font::glyphProvided(unsigned int glyph) const
	{
		return TTF_GlyphIsProvided(ptr, glyph);
	}
	
	int Font::providedGlyph(unsigned int glyph) const
	{
		return TTF_GlyphIsProvided(ptr, glyph);
	}
	
	void Font::glyphMetrics(unsigned int glyph, int* minx, int* maxx, int* miny, int* maxy, int* advance) const
	{
		TTF_CHECKERROR(TTF_GlyphMetrics(ptr, glyph, minx, maxx, miny, maxy, advance), 0);
	}
	
	void Font::sizeText(const std::string text, int* w, int* h) const
	{
		TTF_CHECKERROR(TTF_SizeText(ptr, text.c_str(), w, h), 0);
	}
	
	void Font::textSize(const std::string text, int* w, int* h) const
	{
		TTF_CHECKERROR(TTF_SizeText(ptr, text.c_str(), w, h), 0);
	}
	
	void Font::sizeUTF8(const std::string text, int* w, int* h) const
	{
		TTF_CHECKERROR(TTF_SizeUTF8(ptr, text.c_str(), w, h), 0);
	}
	
	void Font::sizeUnicode(const std::basic_string<char16_t> text, int* w, int* h) const
	{
		
		TTF_CHECKERROR(TTF_SizeUNICODE(ptr, (const unsigned short*)text.c_str(), w, h), 0);
	}
	
	void Font::sizeUnicode(const unsigned short* text, int* w, int* h) const
	{
		TTF_CHECKERROR(TTF_SizeUNICODE(ptr, text, w, h), 0);
	}
	
	void Font::sizeUnicode(const char16_t* text, int* w, int* h) const
	{
		TTF_CHECKERROR(TTF_SizeUNICODE(ptr, (const unsigned short*)text, w, h), 0);
	}
	
	Surface* Font::surfaceSolid(const std::string text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Solid(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceSolid(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Solid(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUTF8Solid(const std::string text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Solid(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUTF8Solid(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Solid(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeSolid(const unsigned short* text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeSolid(const unsigned short* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeSolid(const char16_t* text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeSolid(const char16_t* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeSolid(const std::basic_string<char16_t> text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeSolid(const std::basic_string<char16_t> text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceGlyphSolid(unsigned short glyph, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Solid(ptr, glyph, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceGlyphSolid(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Solid(ptr, glyph, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceShaded(const std::string text, const Color fgColor, const Color bgColor) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Shaded(ptr, text.c_str(), *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceShaded(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Shaded(ptr, text.c_str(), SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUTF8Shaded(const std::string text, const Color fgColor, const Color bgColor) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Shaded(ptr, text.c_str(), *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUTF8Shaded(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Shaded(ptr, text.c_str(), SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeShaded(const unsigned short* text, const Color fgColor, const Color bgColor) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, text, *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeShaded(const unsigned short* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, text, SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeShaded(const char16_t* text, const Color fgColor, const Color bgColor) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text, *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeShaded(const char16_t* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text, SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeShaded(const std::basic_string<char16_t> text, const Color fgColor, const Color bgColor) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text.c_str(), *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeShaded(const std::basic_string<char16_t> text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text.c_str(), SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceGlyphShaded(unsigned short glyph, const Color fgColor, const Color bgColor) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Shaded(ptr, glyph, *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceGlyphShaded(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Shaded(ptr, glyph, SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceBlended(const std::string text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceBlended(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUTF8Blended(const std::string text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Blended(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUTF8Blended(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Blended(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeBlended(const unsigned short* text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeBlended(const unsigned short* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeBlended(const char16_t* text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeBlended(const char16_t* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeBlended(const std::basic_string<char16_t> text, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceUnicodeBlended(const std::basic_string<char16_t> text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceGlyphBlended(unsigned short glyph, const Color color) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Blended(ptr, glyph, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
	}
	
	Surface* Font::surfaceGlyphBlended(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Blended(ptr, glyph, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
	}
	
	
}