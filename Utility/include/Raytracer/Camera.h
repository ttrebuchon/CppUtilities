#pragma once
#include "Types.h"
#include <string>

namespace Util
{
namespace Raytracer
{
	
	class Camera : public std::enable_shared_from_this<Camera>, public RaytracerItem
	{
		private:
		int dims[2];
		double viewpointDims[2];
		vector_t viewpoint;
		image_t* img;
		
		
		public:
		Camera(std::string name, double w, double h, vector_t viewpoint);
		
		
		void setPixel(int x, int y, const dpixel_t);
		pixel_t getPixel(int x, int y) const;
		vector_t dir(int x, int y) const;
		int x() const { return dims[0]; }
		int y() const { return dims[1]; }
		vector_t view() const { return viewpoint; }
		
		void setImgDims(const int x, const int y);
		void setImg(image_t*);
		
		virtual std::string toString() const override;
	};
}
}