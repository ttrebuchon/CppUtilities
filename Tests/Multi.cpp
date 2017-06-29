#include "../Tests_Helpers.h"

#include <QUtils/Multi/Multi.h>
#include <exception>
#include <type_traits>

void someFunc(int x)
{
	for (int i = 0; i < x; i++)
	{
		
	}
	dout << "someFunc(" << x << ")\n";
}

class FooClass
{
	int X = 0;
	
	public:
	
	virtual int x()
	{
		return X++;
	}
};

class FooClass2 : public QUtils::Multi::Lockable
{
	std::string str;
	
	
	public:
	
	void add(std::string s)
	{
		str += s;
	}
	
	std::string get() const
	{
		return str;
	}
};

bool Test_Multi()
{
	auto F2 = [](auto x) -> auto
	{
		dout << "F2(" << x << ")\n";
		return 42;
	};
	std::thread t(someFunc, 4);
	std::thread t2(F2, 8);
	
	auto t2_2 = std::async(F2, 7);
	
	t2_2.wait();
	dout << "t2_2: " << t2_2.get() << "\n";
	t2.join();
	t.join();
	
	FooClass c;
	dout << c.x() << "\n";
	QUtils::Multi::Mutexed<FooClass> cl(c);
	cl.lock();
	cl.unlock();
	cl.lock();
	dout << cl->x() << std::endl;
	cl.unlock();
	cl.unlock();
	
	auto inc = [] (auto* obj, auto count, auto prefix) -> decltype(count) {
		typedef decltype(count) Num;
		Num i;
		for (i = 0; i < count; i++)
		{
			obj->lock();
			dout << prefix << (*obj)->x() << ", ";
			obj->unlock();
		}
		return i;
	};
	
	/*for (int i = 0; i < 10000; i++)
	{
		cl.lock();
		dout << cl->x() << ", ";
		cl.unlock();
	}*/
	const int count = 10000;
	std::thread clt1(inc, &cl, count/2, "a");
	std::thread clt2(inc, &cl, count - count/2, "b");
	
	clt1.join();
	clt2.join();
	
	
	dout << "\n";
	
	
	FooClass2 c2;
	c2.lock();
	c2.add("Hello, world! ");
	c2.unlock();
	
	
	return true;
}