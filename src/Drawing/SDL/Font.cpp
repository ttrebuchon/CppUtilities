#include <QUtils/Drawing/SDL/Font.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/Surface.h>

#include "IfTTF.h"


namespace QUtils::Drawing::SDL
{
	Font::Font() : Base(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
		#else
		throw NotAvail();
		#endif
	}
	
	Font::Font(TTF_Font* ptr) : Base(ptr)
	{
		#ifdef QUTILS_HAS_SDL2
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	Font::~Font()
	{
		#ifdef QUTILS_HAS_SDL2
		if (ptr != NULL)
		{
			TTF_CloseFont(ptr);
		}
		#endif
	}
	
	Font* Font::Open(const std::string file, int size)
	{
		#ifdef QUTILS_HAS_SDL2
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
		TTF_Font* ptr;
		TTF_ERRORIF(ptr = TTF_OpenFont(file.c_str(), size), NULL);
		return Font::getObject(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	Font* Font::OpenFont(const std::string file, int size)
	{
		#ifdef QUTILS_HAS_SDL2
		if (!TTF_WasInit())
		{
			TTF_CHECKERROR(TTF_Init(), 0);
		}
		TTF_Font* ptr;
		TTF_ERRORIF(ptr = TTF_OpenFont(file.c_str(), size), NULL);
		return Font::getObject(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	FontStyle Font::style() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_EnumFontStyle(TTF_GetFontStyle(ptr));
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::style(FontStyle style)
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_SetFontStyle(ptr, SDL_RawFontStyle(style));
		#else
		throw NotAvail();
		#endif
	}
		
	int Font::outline() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_GetFontOutline(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::outline(int val)
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_SetFontOutline(ptr, val);
		#else
		throw NotAvail();
		#endif
	}
		
	FontHinting Font::hinting() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_EnumFontHinting(TTF_GetFontHinting(ptr));
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::hinting(FontHinting hinting)
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_SetFontHinting(ptr, SDL_RawFontHinting(hinting));
		#else
		throw NotAvail();
		#endif
	}
		
	bool Font::kerning() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_GetFontKerning(ptr) != 0;
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::kerning(bool val)
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_SetFontKerning(ptr, (int)val);
		#else
		throw NotAvail();
		#endif
	}
		
	int Font::height() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontHeight(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	int Font::ascent() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontAscent(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	int Font::descent() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontDescent(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	int Font::lineSkip() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontLineSkip(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	long Font::faces() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontFaces(ptr);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Font::fixedWidth() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontFaceIsFixedWidth(ptr) > 0;
		#else
		throw NotAvail();
		#endif
	}
	
	bool Font::isFixedWidth() const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_FontFaceIsFixedWidth(ptr) > 0;
		#else
		throw NotAvail();
		#endif
	}
	
	std::string Font::familyName() const
	{
		#ifdef QUTILS_HAS_SDL2
		return std::string(TTF_FontFaceFamilyName(ptr));
		#else
		throw NotAvail();
		#endif
	}
	
	std::string Font::styleName() const
	{
		#ifdef QUTILS_HAS_SDL2
		return std::string(TTF_FontFaceStyleName(ptr));
		#else
		throw NotAvail();
		#endif
	}
	
	int Font::glyphProvided(unsigned int glyph) const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_GlyphIsProvided(ptr, glyph);
		#else
		throw NotAvail();
		#endif
	}
	
	int Font::providedGlyph(unsigned int glyph) const
	{
		#ifdef QUTILS_HAS_SDL2
		return TTF_GlyphIsProvided(ptr, glyph);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::glyphMetrics(unsigned int glyph, int* minx, int* maxx, int* miny, int* maxy, int* advance) const
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_CHECKERROR(TTF_GlyphMetrics(ptr, glyph, minx, maxx, miny, maxy, advance), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::sizeText(const std::string text, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_CHECKERROR(TTF_SizeText(ptr, text.c_str(), w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::textSize(const std::string text, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_CHECKERROR(TTF_SizeText(ptr, text.c_str(), w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::sizeUTF8(const std::string text, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_CHECKERROR(TTF_SizeUTF8(ptr, text.c_str(), w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::sizeUnicode(const std::basic_string<char16_t> text, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		
		TTF_CHECKERROR(TTF_SizeUNICODE(ptr, (const unsigned short*)text.c_str(), w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::sizeUnicode(const unsigned short* text, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_CHECKERROR(TTF_SizeUNICODE(ptr, text, w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	void Font::sizeUnicode(const char16_t* text, int* w, int* h) const
	{
		#ifdef QUTILS_HAS_SDL2
		TTF_CHECKERROR(TTF_SizeUNICODE(ptr, (const unsigned short*)text, w, h), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceSolid(const std::string text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Solid(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceSolid(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Solid(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUTF8Solid(const std::string text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Solid(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUTF8Solid(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Solid(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeSolid(const unsigned short* text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeSolid(const unsigned short* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeSolid(const char16_t* text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeSolid(const char16_t* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeSolid(const std::basic_string<char16_t> text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeSolid(const std::basic_string<char16_t> text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Solid(ptr, (const unsigned short*)text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceGlyphSolid(unsigned short glyph, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Solid(ptr, glyph, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceGlyphSolid(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Solid(ptr, glyph, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceShaded(const std::string text, const Color fgColor, const Color bgColor) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Shaded(ptr, text.c_str(), *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceShaded(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Shaded(ptr, text.c_str(), SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUTF8Shaded(const std::string text, const Color fgColor, const Color bgColor) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Shaded(ptr, text.c_str(), *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUTF8Shaded(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Shaded(ptr, text.c_str(), SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeShaded(const unsigned short* text, const Color fgColor, const Color bgColor) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, text, *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeShaded(const unsigned short* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, text, SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeShaded(const char16_t* text, const Color fgColor, const Color bgColor) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text, *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeShaded(const char16_t* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text, SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeShaded(const std::basic_string<char16_t> text, const Color fgColor, const Color bgColor) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text.c_str(), *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeShaded(const std::basic_string<char16_t> text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Shaded(ptr, (const unsigned short*)text.c_str(), SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceGlyphShaded(unsigned short glyph, const Color fgColor, const Color bgColor) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Shaded(ptr, glyph, *((SDL_Color*)&bgColor), *((SDL_Color*)&fgColor)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceGlyphShaded(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Shaded(ptr, glyph, SDL_Color{r, g, b, alpha}, SDL_Color{r2, g2, b2, alpha2}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceBlended(const std::string text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceBlended(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUTF8Blended(const std::string text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Blended(ptr, text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUTF8Blended(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUTF8_Blended(ptr, text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeBlended(const unsigned short* text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeBlended(const unsigned short* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeBlended(const char16_t* text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeBlended(const char16_t* text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeBlended(const std::basic_string<char16_t> text, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text.c_str(), *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceUnicodeBlended(const std::basic_string<char16_t> text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderUNICODE_Blended(ptr, (const unsigned short*)text.c_str(), SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceGlyphBlended(unsigned short glyph, const Color color) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Blended(ptr, glyph, *((SDL_Color*)&color)), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceGlyphBlended(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderGlyph_Blended(ptr, glyph, SDL_Color{r, g, b, alpha}), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceBlendedWrapped(const std::string text, const Color color, const int wrapLen) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended_Wrapped(ptr, text.c_str(), *((SDL_Color*)&color), wrapLen), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceBlendedWrapped(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, const int wrapLen) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended_Wrapped(ptr, text.c_str(), SDL_Color{r, g, b, alpha}, wrapLen), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceBlendedWrappedWithRatio(const std::string text, const Color color, const double ratio) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended_Wrapped(ptr, text.c_str(), *((SDL_Color*)&color), ratio*this->height()), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	Surface* Font::surfaceBlendedWrappedWithRatio(const std::string text, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, const double ratio) const
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Surface* surfPtr;
		TTF_ERRORIF(surfPtr = TTF_RenderText_Blended_Wrapped(ptr, text.c_str(), SDL_Color{r, g, b, alpha}, ratio*this->height()), NULL);
		return Surface::getObject(surfPtr);
		#else
		throw NotAvail();
		#endif
	}
	
	
}