#pragma once
#include "Version.h"

namespace QUtils::Drawing::SDL
{
	enum struct PixelFormat : unsigned int
	{
		Unknown,
		Index1LSB,
		Index1MSB,
		Index4LSB,
		Index4MSB,
		Index8,
		RGB332,
		RGB444,
		RGB555,
		BGR555,
		ARGB4444,
		RGBA4444,
		ABGR4444,
		BGRA4444,
		ARGB1555,
		RGBA5551,
		ABGR1555,
		BGRA5551,
		RGB565,
		BGR565,
		RGB24,
		BGR24,
		RGB888,
		RGBX8888,
		BGR888,
		BGRX8888,
		ARGB8888,
		RGBA8888,
		ABGR8888,
		BGRA8888,
		ARGB2101010,
		#if SDL_VERSION_MIN(2,0,5)
		RGBA32,
		ARGB32,
		BGRA32,
		ABGR32,
		#endif
		YV12,
		IYUV,
		YUY2,
		UYVY,
		YVYU,
		#if SDL_VERSION_MIN(2,0,4)
		NV12,
		NV21,
		#endif
	};
	
	unsigned int SDL_RawPixelFormat(PixelFormat);
	PixelFormat SDL_EnumPixelFormat(unsigned int);
}