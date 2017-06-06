#include "../Tests.h"
#include <Raytracer/Raytracer.h>

using namespace Utils;
using namespace Raytracer;

bool Testing::Raytrace()
{
	Model* mod = new Model("TestModel1");
	const int x=10, y = 10;
	auto img = mod->go(x, y);
	for (auto i = img->pix; i != img->pix + x*y; i++)
	{
		auto pix = *i;
		dout << "(" << pix.R << ", " << pix.G << ", " << pix.B << ")" << endl;
	}
	
	delete mod;
	return true;
}