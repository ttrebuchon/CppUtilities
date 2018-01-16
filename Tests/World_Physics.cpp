#include "../Tests_Helpers.h"

#include <QUtils/World/Physics/Physics.h>
#include <QUtils/GUI/SDL/SDL.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/Sleep/Sleep.h>



constexpr QUtils::World::Vector<double> testF()
{
	return QUtils::World::Vector<double>();
}

QUtils::GUI::ViewComponent* setupGUI(QUtils::GUI::SDL::SDLAppWindow*);
void resetGUI(QUtils::GUI::SDL::SDLAppWindow*, QUtils::GUI::ViewComponent*);

bool Test_World_Physics(QUtils::GUI::SDL::SDLAppWindow* window)
{
	using namespace QUtils::World::Physics;
	
	
	QUtils::World::Vector<double> v = QUtils::World::Vector<double>{1, 2, 3};
	QUtils::World::Vector<float> v2 = {4, 5, 6};
	
	auto v3 = v + v2;
	dout << to_string(v3) << std::endl;
	
	QUtils::World::Vector<int> v4;
	v4 += v3;
	dout << to_string(v4) << std::endl;
	
	constexpr auto cv1 = testF();
	constexpr QUtils::World::Vector<double> cv2(1, 2, 3);
	
	static_assert(cv1 - cv2 + cv2 == cv1);
	
	QUtils::World::Vector<QUtils::World::Vector<double>> m1;
	m1.x.x = 1;
	
	dout << to_string(m1) << std::endl;
	
	
	using namespace QUtils::World;
	
	{
	
	Vector<double> v(1, 1, 0);
	Vector<double> v2(1, 1, 0);
	auto v3 = v.cross(v2);
	assert_ex(v3.x == 0);
	assert_ex(v3.y == 0);
	assert_ex(v3.z == 0);
	
	static_assert(Vector<double>(1, 1, 0).cross(Vector<double>(1, 1, 0)) == Vector<double>(0, 0, 0), "");
	
	v2.x = -1;
	v3 = v.cross(v2);
	assert_ex(v3.x == 0);
	assert_ex(v3.y == 0);
	assert_ex(v3.z == 2);
	
	static_assert(Vector<double>(1, 1, 0).cross(Vector<double>(-1, 1, 0)) == Vector<double>(0, 0, 2), "");
	
	}
	
	{
	
	Vector<double> v(1, 1, 0);
	Vector<double> v2(1, 1, 0);
	auto d = v.dot(v2);
	assert_ex(d == 2);
	
	static_assert(Vector<double>(1, 1, 0).dot(Vector<double>(1, 1, 0)) == 2, "");
	
	v2.x = -1;
	d = v.dot(v2);
	assert_ex(d == 0);
	
	static_assert(Vector<double>(1, 1, 0).dot(Vector<double>(-1, 1, 0)) == 0, "");
	
	}
	
	typedef Vector<double> Vec;
	
	{
		Vec v(1, 0, 0);
		assert_ex(v.value() == 1);
		static_assert(Vec(1, 0, 0).magnitude() == 1);
		static_assert(Vec(1, 0, 0).value() == 1);
		
		
	}
	
	{
		typedef Vector<Vec> Mat;
		constexpr Mat m{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
		
		static_assert(m.x.x == 1, "");
		static_assert(m.x.y == 0, "");
		static_assert(m.x.z == 0, "");
		
		static_assert(m.y.x == 0, "");
		static_assert(m.y.y == 1, "");
		static_assert(m.y.z == 0, "");
		
		static_assert(m.z.x == 0, "");
		static_assert(m.z.y == 0, "");
		static_assert(m.z.z == 1, "");
		
		constexpr Vec v(1, 2, 3);
		constexpr Vec r = m.dot(v);
		static_assert(r == v, "");
		dout << "Matrix Math: ";
		dout << to_string(r) << std::endl;
		
		dout << to_string(m) << std::endl;
		
		constexpr auto r2 = v.dot(m);
		
		dout << to_string(r2) << "\n";
	}
	
	QUtils::GUI::ViewComponent* orig = NULL;
	if (window != NULL)
	{
		orig = setupGUI(window);
	}
	
	
	
	{
		
		
		
		
	}
	
	
	
	
	
	
	
	
	
	
	{
		System<double> sys;
		sys.timescale = pow(10, -3);
		sys.env = std::make_shared<Environment<double>>();
		sys.env->gravity = pow(10, 11);
		auto part = std::make_shared<StandardParticle<double>>();
		sys.particles.push_back(part);
		
		
		sys.env->forces.push_back(std::make_shared<UniformGravity<double>>(Vec(0, -10, 0)));
		sys.env->forces.push_back(std::make_shared<MagneticFieldForce<double>>());
		sys.env->fields.push_back(std::make_shared<UniformMagnetic<double>>(Vec(10, 0, 0)));
		
		part->_mass = 1000;
		part->properties["charge"] = {-1000, 0, 0};
		
		auto part2 = std::make_shared<StandardParticle<double>>();
		sys.particles.push_back(part2);
		part2->position({1000, 20, 0});
		part2->_mass = 1;
		part2->properties["charge"] = {1, 0, 0};
		
		dout << "\n\n" << to_string(part->position()) << "\n";
		
		for (int i = 0; i < 10000; ++i)
		{
			sys.step();
			if (i % 1000 == 999)
			{
			dout << "\n\nTime: " << sys.ticks*sys.timescale << "s\n";
			dout << "P1: " << to_string(part->position()) << "\n\tv: " << to_string(part->velocity()) << "\n\tF: " << to_string(sys.forces.at(part)) << "\n";
			dout << "P2: " << to_string(part2->position()) << "\n\tv: " << to_string(part2->velocity()) << "\n\tF: " << to_string(sys.forces.at(part2)) << "\n\n";
			}
			
		}
		
	}
	if (window != NULL && orig != NULL)
	{
		resetGUI(window, orig);
	}
	
	return true;
}







QUtils::GUI::ViewComponent* setupGUI(QUtils::GUI::SDL::SDLAppWindow* window)
{
	try
	{
	const int w = window->width();
	const int h = window->height();
	const bool TOUCH = true;
	
	using namespace QUtils::GUI;
	using namespace QUtils::GUI::SDL;
	using namespace QUtils::Drawing::SDL;
	
	auto orig = window->replaceView(NULL);
	assert_ex(orig->window == NULL);
	while (window->updateBlocked())
	{
		window->unblockUpdate();
	}
	
	dout << "(" << window->width() << ", " << window->height() << ")\n" << std::flush;
	
	assert_ex(window->width() == w);
	assert_ex(window->height() == h);
	
	Renderer* ren;
	
	auto tex = window->invokeUI([=, &ren]() -> Texture*
	{
	auto tmp = new Texture(window->getRenderer(), PixelFormat::RGBA8888, TextureAccess::Target, w, h);
	ren = window->getRenderer();
	ren->target(tmp);
	ren->setDrawColor(0, 0, 0, 255);
	ren->clear();
	ren->setDrawColor(255, 255, 255, 255);
	ren->fillRect({0, 0, w, h});
	ren->renderPresent();
	ren->target(NULL);
	return tmp;
	}).get();
	
	
	#define TEXCOMP "PhysTexComp"
	auto texComp = new SDLTextureViewComponent(TEXCOMP, TOUCH, tex);
	dout << "TexComp id: '" << texComp->id << "'\n";
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == NULL);
	assert_ex(texComp->id == TEXCOMP);
	
	assert_ex(window->replaceView(texComp) == NULL);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == window);
	
	window->unblockUpdate();
	assert_ex(!window->updateBlocked());
	assert_ex(window->replaceView(NULL) == texComp);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == NULL);
	
	
	dout << "Render Successful\n";
	
	
	
	
	auto texView = new SDLAbsoluteTextureView("PhysAbsTextureView", TOUCH, w, h);
	dout << "TexView Created\n";
	
	texView->addChild(texComp, 0, 0, 1, 0.5);
	dout << "First child added\n";
	
	
	auto tex2 = window->invokeUI([=]()
	{
		auto tex2 = new Texture(ren, PixelFormat::RGBA8888, TextureAccess::Target, w, h);
	window->blockUpdate();
	ren->target(tex2);
	ren->setDrawColor(0, 100, 255, 255);
	ren->clear();
	ren->fillRect(0, 0, w, h);
	ren->renderPresent();
	return tex2;
	}).get();
	
	auto texComp2 = new SDLTextureViewComponent("TexComp2", TOUCH, tex2);
	dout << "Second child created\n";
	texView->addChild(texComp2, 0.5, 0, 0.5, 1);
	dout << "Second child added\n";
	
	texComp2->onFingerDown += [](auto...x)
	{
		dout << "\nTex Comp 2 Clicked!\n\n";
	};
	
	texComp->onFingerDown += [](auto...x)
	{
		dout << "\nTex Comp Clicked!\n\n";
	};
	
	
	texComp2->opacity(1);
	assert_ex(texComp2->opacity() == 1);
	
	
	window->replaceView(texView);
	dout << "Window view set\n";
	assert_ex(window->updateBlocked());
	window->unblockUpdate();
	assert_ex(!window->updateBlocked());
	window->invokeUpdate().get();
	dout << "Window updated\n";
	assert_ex(!window->updateBlocked());
	dout << "Handling Events...\n";
	window->handleEvents();
	dout << "Handled" << std::endl;
	
	QUtils::sleep(5000);
	
	return orig;
	}
	catch (...)
	{
		return NULL;
	}
}


void resetGUI(QUtils::GUI::SDL::SDLAppWindow* window, QUtils::GUI::ViewComponent* orig)
{
	window->replaceView(orig);
}