#include "../Tests.h"
#include <Raytracer/Raytracer.h>
#include <fstream>

using namespace Utils;
using namespace Raytracer;

void writePPM(std::string filename, int w, int h, pixel_t* bitmap);

bool Testing::Raytrace()
{
	Model* mod = new Model("TestModel1", 100);
	mod->initCamera(8, 6, vector_t(4, 3, 4));
	
	
	auto carpet = std::make_shared<Material>("Carpet", dpixel_t(5, 3, 3), dpixel_t(5, 5, 5), 0, 0, 0);
	auto floor = std::make_shared<Plane>("Floor", carpet, vector_t(0, 1, 0), vector_t(0, 0, 0));
	mod->add(floor);
	
	
	auto wallpaper = std::make_shared<Material>("Wallpaper", dpixel_t(3, 3, 5), dpixel_t(5, 5, 5), 0, 0, 0);
	auto wall = std::make_shared<Plane>("Wall", wallpaper, vector_t(0, 0, 1), vector_t(0, 0, -5));
	mod->add(wall);
	
	auto overhead = std::make_shared<Light>("Overhead", vector_t(4, 5, 5), dpixel_t(8, 5, 5));
	mod->add(overhead);
	
	
	//dout << std::endl << carpet->toString() << std::endl << floor->toString() << std::endl << overhead->toString() << std::endl;
	
	
	const int x = 640, y = 480;
	auto img = mod->go(x, y);
	for (auto i = img->pix; i != img->pix + x*y; i++)
	{
		//auto pix = *i;
		//dout << "(" << pix.R << ", " << pix.G << ", " << pix.B << ")" << endl;
	}
	
	delete mod;
	
	writePPM("Test.ppm", x, y, img->pix);
	delete img;
	
	return true;
}



void writePPM(std::string filename, int w, int h, pixel_t* bitmap)
{
	std::ofstream file(filename);
	std::string head = "P6\t";
	head += std::to_string(w) + "\t" + std::to_string(h) + "\n" + "255" + "\n";
	file.write(head.c_str(), head.length());
	char pixel[3];
	for (auto it = bitmap; it != bitmap+w*h; it++)
	{
		pixel[0] = it->R;
		pixel[1] = it->G;
		pixel[2] = it->B;
		file.write(pixel, 3);
	}
	file.close();
}