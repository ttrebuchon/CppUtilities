#pragma once
#include "GenericImage.h"


namespace QUtils
{
namespace Raytracer
{
namespace Images
{
	class JPGImage : public GenericImage
	{
		protected:
		
		
		public:
		JPGImage(const unsigned int w, const unsigned int h) : GenericImage(w, h)
		{}
		
		virtual ~JPGImage();
		
		virtual bool save(const std::string filename) const override;
		
		virtual bool load(const std::string filename) override;
		
		virtual JPGImage* clone() const override;
	};
}
}
}