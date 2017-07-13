#include "../Tests_Helpers.h"
#include <QUtils/Raytracer/Raytracer.h>
#include <QUtils/Raytracer/Images/Images.h>
#include <fstream>

using namespace QUtils;
using namespace Raytracer;

void writePPM(std::string filename, int w, int h, pixel_t* bitmap);

pixel_t* gradient(pixel_t*, int w, int h);

pixel_t* gray(pixel_t*, int w, int h);
pixel_t* BW(pixel_t*, int w, int h);

bool Test_Raytrace()
{
	Model* mod = new Model("TestModel1", 40, 1);
	double w = 8;
	//double h = 6;
	double h = 4.5;
	mod->initCamera(w, h, vector_t(w/2, h/2, 4));
	
	
	auto carpet = std::make_shared<Material>("Carpet", dpixel_t(0, 0, 0), dpixel_t(0.5, 0.5, 0.5), 0.9, 0, 0);
	auto wallpaper = std::make_shared<Material>("Wallpaper", dpixel_t(3, 3, 5), dpixel_t(5, 5, 5), 0, 0, 0);
	auto metal = std::make_shared<Material>("Metal", dpixel_t(1, 1, 1), dpixel_t(0, 0, 0), 0.2, 0, 0);
	auto gray = std::make_shared<Material>("Gray", dpixel_t(1, 1, 1), dpixel_t(5, 5, 5), 0.6, 0, 0);
	auto red = std::make_shared<Material>("Red", dpixel_t(0, 0, 0), dpixel_t(4, 1.5, 1.5), 0, 0, 0);
	auto clear = std::make_shared<Material>("Clear", dpixel_t(0, 0, 0), dpixel_t(4, 4, 4), 0, 0, 0.6);
	
	
	auto ceilingL = std::make_shared<Light>("Ceiling", vector_t(4, 8, -4), dpixel_t(5, 3, 3));
	auto frontL = std::make_shared<Light>("Front", vector_t(6, 8, 0), dpixel_t(14, 14, 14));
	auto floorL = std::make_shared<Light>("FloorLight", vector_t(6, 0, -5), dpixel_t(3, 3, 3));
	auto overhead = std::make_shared<Light>("Overhead", vector_t(w/2, 5*h/6, 5), dpixel_t(5, 5, 5));
	
	
	
	
	auto wall = std::make_shared<Plane>("Wall", wallpaper, vector_t(0, 0, 1), vector_t(0, 0, -5));
	
	auto ball = std::make_shared<Sphere>("Ball", metal, 1, vector_t(w/2, 3.1, 1));
	
	auto backwall = std::make_shared<Plane>("Backwall", wallpaper, vector_t(0, 0, -1), vector_t(0, 0, 13));
	
	auto left = std::make_shared<Sphere>("Left", clear, 1, vector_t(6, 3, -3));
	auto right = std::make_shared<Sphere>("Right", red, 1, vector_t(6, 3, -4));
	auto floor = std::make_shared<Plane>("Floor", carpet, vector_t(0, 1, 0), vector_t(0, 0, 0));
	
	mod->add(left);
	mod->add(right);
	mod->add(floor);
	//mod->add(ceilingL);
	mod->add(frontL);
	mod->add(floorL);
	mod->add(wall);
	
	
	
	
	
	//const int x = 640, y = 480;
	const int x = 1920, y = 1080;
	//const int x=640, y = 360;
	
	//auto imgO = mod->go(x, y);
	//QUtils::Raytracer::pixel_t* img = *(imgO);
	
	//dout << "Writing file..." << std::endl;
	//writePPM("Test.ppm", x, y, img);
	//delete imgO;
	
	Images::JPGImage jImg(x, y);
	mod->go(&jImg, x, y);
	dout << "Writing jpeg file..." << std::endl;
	assert_ex(jImg.save("TestImg.jpg"));
	
	
	
	/*dout << "Taking B&W...\n";
	jImg.BWConvert();
	
	assert_ex(jImg.save("BW_TestImg.jpg"));*/
	
	right->move(vector_t(-1, 0, -1));
	
	dout << "Running Img_2...\n";
	
	Images::JPGImage jImg_2(x, y);
	mod->go(&jImg_2, x, y);
	
	dout << "Saving image 2\n";
	
	assert_ex(jImg_2.save("TestImg_2.jpg"));
	
	dout << "Cloning image 2\n";
	
	Images::JPGImage* jImg_2_bak = jImg_2.clone();
	
	dout << "Getting diff...\n";
	jImg_2.diff(&jImg);
	
	dout << "Saving\n";
	assert_ex(jImg_2.save("Diff_Test.jpg"));
	
	dout << "BWConvert\n";
	jImg_2.BWConvert();
	
	dout << "Saving\n";
	assert_ex(jImg_2.save("Diff_Test_BW.jpg"));
	
	dout << "Converting bak and 2 to BW\n";
	jImg_2_bak->BWConvert();
	jImg.BWConvert();
	
	dout << "Diffing\n";
	
	jImg_2_bak->diff(&jImg);
	
	dout << "Saving\n";
	
	assert_ex(jImg_2_bak->save("BW_Diff_Test.jpg"));
	
	
	
	
	
	
	
	
	
	/*ball->move(vector_t(4, 0, 0));
	
	img = mod->go(x, y);
	writePPM("Test.ppm", x, y, img);
	delete[] img;*/
	
	
	delete mod;
	delete jImg_2_bak;
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


pixel_t* gradient(pixel_t* src, int w, int h)
{
	auto row = [w] (pixel_t* ptr, int y) -> pixel_t*
	{
		return ptr + y*w;
	};
	
	
	pixel_t* img = new pixel_t[w*h];
	
	for (int y = 1; y < h - 1; y++)
	{
		auto o = row(src, y);
		auto n = row(img, y);
		
		auto above = row(src, y-1);
		auto below = row(src, y+1);
		for (int x = 1; x < w - 1; x++)
		{
			n[x] = (o[x-1] - o[x+1] + above[x] - below[x])*0.25;
			
		}
		
	}
	return img;
}

pixel_t* gray(pixel_t* src, int w, int h)
{
	pixel_t* dst = new pixel_t[w*h];
	for (auto i = 0; i < w*h; i++)
	{
		auto pix = src[i];
		unsigned char avg = (pix.R + pix.G + pix.B)/3;
		dst[i] = pixel_t(avg, avg, avg);
	}
	return dst;
}