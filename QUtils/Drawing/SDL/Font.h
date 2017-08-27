#pragma once

#include "SDLObject.h"
#include "FontStyle.h"
#include "FontHinting.h"
#include "Color.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;




namespace QUtils::Drawing::SDL
{
	class Surface;
	
	class Font : public Internal::SDLObject<TTF_Font, Font>
	{
		typedef Internal::SDLObject<TTF_Font, Font> Base;
		friend Base;
		protected:
		
		Font();
		Font(TTF_Font*);
		
		public:
		
		static Font* Open(const std::string file, int size);
		static Font* OpenFont(const std::string file, int size);
		
		
		FontStyle style() const;
		void style(FontStyle);
		
		int outline() const;
		void outline(int);
		
		FontHinting hinting() const;
		void hinting(FontHinting);
		
		bool kerning() const;
		void kerning(bool);
		
		int height() const;
		int ascent() const;
		int descent() const;
		int lineSkip() const;
		long faces() const;
		bool fixedWidth() const;
		bool isFixedWidth() const;
		std::string familyName() const;
		std::string styleName() const;
		int glyphProvided(unsigned int) const;
		int providedGlyph(unsigned int) const;
		void glyphMetrics(unsigned int glyph, int* minx, int* maxx, int* miny, int* maxy, int* advance) const;
		void sizeText(const std::string, int* w, int* h) const;
		void textSize(const std::string, int* w, int* h) const;
		void sizeUTF8(const std::string, int* w, int* h) const;
		void sizeUnicode(const std::basic_string<char16_t>, int* w, int* h) const;
		void sizeUnicode(const unsigned short*, int* w, int* h) const;
		void sizeUnicode(const char16_t*, int* w, int* h) const;
		
		
		Surface* surfaceSolid(const std::string, const Color) const;
		Surface* surfaceSolid(const std::string, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUTF8Solid(const std::string, const Color) const;
		Surface* surfaceUTF8Solid(const std::string, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUnicodeSolid(const unsigned short*, const Color) const;
		Surface* surfaceUnicodeSolid(const unsigned short*, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUnicodeSolid(const char16_t*, const Color) const;
		Surface* surfaceUnicodeSolid(const char16_t*, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUnicodeSolid(const std::basic_string<char16_t>, const Color) const;
		Surface* surfaceUnicodeSolid(const std::basic_string<char16_t>, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceGlyphSolid(unsigned short glyph, const Color) const;
		Surface* surfaceGlyphSolid(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		
		
		
		Surface* surfaceShaded(const std::string, const Color, const Color) const;
		Surface* surfaceShaded(const std::string, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const;
		Surface* surfaceUTF8Shaded(const std::string, const Color, const Color) const;
		Surface* surfaceUTF8Shaded(const std::string, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const;
		Surface* surfaceUnicodeShaded(const unsigned short*, const Color, const Color) const;
		Surface* surfaceUnicodeShaded(const unsigned short*, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const;
		Surface* surfaceUnicodeShaded(const char16_t*, const Color, const Color) const;
		Surface* surfaceUnicodeShaded(const char16_t*, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const;
		Surface* surfaceUnicodeShaded(const std::basic_string<char16_t>, const Color, const Color) const;
		Surface* surfaceUnicodeShaded(const std::basic_string<char16_t>, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const;
		Surface* surfaceGlyphShaded(unsigned short glyph, const Color, const Color) const;
		Surface* surfaceGlyphShaded(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, unsigned char r2, unsigned char g2, unsigned char b2, unsigned char alpha2) const;
		
		
		
		Surface* surfaceBlended(const std::string, const Color) const;
		Surface* surfaceBlended(const std::string, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUTF8Blended(const std::string, const Color) const;
		Surface* surfaceUTF8Blended(const std::string, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUnicodeBlended(const unsigned short*, const Color) const;
		Surface* surfaceUnicodeBlended(const unsigned short*, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUnicodeBlended(const char16_t*, const Color) const;
		Surface* surfaceUnicodeBlended(const char16_t*, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceUnicodeBlended(const std::basic_string<char16_t>, const Color) const;
		Surface* surfaceUnicodeBlended(const std::basic_string<char16_t>, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		Surface* surfaceGlyphBlended(unsigned short glyph, const Color) const;
		Surface* surfaceGlyphBlended(unsigned short glyph, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha) const;
		
		
	};
}