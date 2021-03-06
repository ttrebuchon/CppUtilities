#pragma once
#include "Types.h"
#include <string>
#include <memory>

namespace QUtils
{
namespace Graphics
{
	class IImage;
}
namespace Raytracer
{
	
	class Camera : public std::enable_shared_from_this<Camera>, public RaytracerItem
	{
		private:
		int dims[2];
		double viewpointDims[2];
		vector_t viewpoint;
		//image_t img;
		Graphics::IImage* img;
		
		
		protected:
		
		
		public:
		Camera(std::string name, double w, double h, vector_t viewpoint);
		
		
		virtual void setPixel(int x, int y, const dpixel_t);
		virtual pixel_t getPixel(int x, int y) const;
		vector_t dir(int x, int y, bool AA = true) const;
		int x() const { return dims[0]; }
		int y() const { return dims[1]; }
		vector_t view() const { return viewpoint; }
		
		virtual void setImgDims(const int x, const int y);
		virtual void setImg(Graphics::IImage*);
		
		virtual std::string toString() const override;
	};
}
}