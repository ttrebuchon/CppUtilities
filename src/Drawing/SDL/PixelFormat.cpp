#include <QUtils/Drawing/SDL/PixelFormat.h>
#include "IfSDL.h"
#include <map>

#ifdef QUTILS_HAS_SDL2

typedef decltype(SDL_PIXELFORMAT_UNKNOWN) PFe;

#endif

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	namespace Helpers
	{
		std::map<PFe, PixelFormat> reverseMap(const std::map<PixelFormat, PFe>& map)
		{
			std::map<PFe, PixelFormat> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFTYPE(x, y) { PixelFormat::x, SDL_PIXELFORMAT_##y, }
	#define DEFTYPE_SAME(x) DEFTYPE(x, x)
	
	static std::map<PixelFormat, PFe> formats = {
		DEFTYPE(Unknown, UNKNOWN),
		DEFTYPE(Index1LSB, INDEX1LSB),
		DEFTYPE(Index1MSB, INDEX1MSB),
		DEFTYPE(Index4LSB, INDEX4LSB),
		DEFTYPE(Index4MSB, INDEX4MSB),
		DEFTYPE(Index8, INDEX8),
		DEFTYPE_SAME(RGB332),
		DEFTYPE_SAME(RGB444),
		DEFTYPE_SAME(RGB555),
		DEFTYPE_SAME(BGR555),
		DEFTYPE_SAME(ARGB4444),
		DEFTYPE_SAME(RGBA4444),
		DEFTYPE_SAME(ABGR4444),
		DEFTYPE_SAME(BGRA4444),
		DEFTYPE_SAME(ARGB1555),
		DEFTYPE_SAME(RGBA5551),
		DEFTYPE_SAME(ABGR1555),
		DEFTYPE_SAME(BGRA5551),
		DEFTYPE_SAME(RGB565),
		DEFTYPE_SAME(BGR565),
		DEFTYPE_SAME(RGB24),
		DEFTYPE_SAME(BGR24),
		DEFTYPE_SAME(RGB888),
		DEFTYPE_SAME(RGBX8888),
		DEFTYPE_SAME(BGR888),
		DEFTYPE_SAME(BGRX8888),
		DEFTYPE_SAME(ARGB8888),
		DEFTYPE_SAME(RGBA8888),
		DEFTYPE_SAME(ABGR8888),
		DEFTYPE_SAME(BGRA8888),
		DEFTYPE_SAME(ARGB2101010),
		#if SDL_VERSION_MIN(2,0,5)
		DEFTYPE_SAME(RGBA32),
		DEFTYPE_SAME(ARGB32),
		DEFTYPE_SAME(BGRA32),
		DEFTYPE_SAME(ABGR32),
		#endif
		DEFTYPE_SAME(YV12),
		DEFTYPE_SAME(IYUV),
		DEFTYPE_SAME(YUY2),
		DEFTYPE_SAME(UYVY),
		DEFTYPE_SAME(YVYU),
		#if SDL_VERSION_MIN(2,0,4)
		DEFTYPE_SAME(NV12),
		DEFTYPE_SAME(NV21),
		#endif
	};
	
	static std::map<PFe, PixelFormat> revFormats = Helpers::reverseMap(formats);
	
	#endif
	
	
	
	unsigned int SDL_RawPixelFormat(PixelFormat format)
	{
		#ifdef QUTILS_HAS_SDL2
		return formats.at(format);
		#else
		throw NotAvail();
		#endif
	}
	
	PixelFormat SDL_EnumPixelFormat(unsigned int format)
	{
		#ifdef QUTILS_HAS_SDL2
		return revFormats.at((PFe)format);
		#else
		throw NotAvail();
		#endif
	}
}