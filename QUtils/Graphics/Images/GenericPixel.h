#pragma once


namespace QUtils
{
namespace Graphics
{
namespace Images
{
	
	struct GenericPixel
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
	};
	
	inline bool operator==(const GenericPixel& pix1, const GenericPixel& pix2)
	{
		return (pix1.R == pix2.R) && (pix1.G == pix2.G) && (pix1.B == pix2.B);
	}
	
	inline bool operator!=(const GenericPixel& pix1, const GenericPixel& pix2)
	{
		return !(pix1 == pix2);
	}
}
}
}