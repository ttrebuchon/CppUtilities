#include "../Tests_Helpers.h"

#include <QUtils/Multi/Multi.h>
#include <QUtils/Multi/Parallel.h>
#include <exception>
#include <type_traits>
#include <vector>
#include <memory>
#include <chrono>

#include <QUtils/Types/CompilerPrint.h>

void someFunc(int x)
{
	for (int i = 0; i < x; i++)
	{
		
	}
	//dout << "someFunc(" << x << ")\n";
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
	{
	auto F2 = [](auto x) -> auto
	{
		//dout << "F2(" << x << ")\n";
		return 42;
	};
	std::thread t(someFunc, 4);
	std::thread t2(F2, 8);
	
	auto t2_2 = std::async(F2, 7);
	
	t2_2.wait();
	//dout << "t2_2: " << t2_2.get() << "\n";
	t2.join();
	t.join();
	
	FooClass c;
	//dout << c.x() << "\n";
	QUtils::Multi::Mutexed<FooClass> cl(c);
	cl.lock();
	cl.unlock();
	cl.lock();
	//dout << cl->x() << std::endl;
	cl.unlock();
	cl.unlock();
	
	auto inc = [] (auto* obj, auto count, auto prefix) -> decltype(count) {
		typedef decltype(count) Num;
		Num i;
		for (i = 0; i < count; i++)
		{
			obj->lock();
			/*dout << prefix << */(*obj)->x()/* << ", "*/;
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
	
	
	//dout << "\n";
	
	
	FooClass2 c2;
	c2.lock();
	c2.add("Hello, world! ");
	c2.unlock();
	}
	
	{
		
		
	class X
	{
		private:
		protected:
		typedef long double K;
		K k;
		
		public:
		X() : k(0)
		{
			
		}
		
		
		virtual K& set(const K nk )
		{
			return (this->k = nk);
		}
		
		K get() const
		{
			return k;
		}
		
		/*virtual void print() const
		{
			dout << get() << "\n";
		}*/
		
	};
	
	class Y : public X
	{
		protected:
		QUtils::Multi::Mutexed<X>* x;
		//using X::print;
		public:
		Y(QUtils::Multi::Mutexed<X>* x) : X(), x(x)
		{
			
		}
		
		
		
		virtual K& set(const K nk) override
		{
			std::lock_guard<decltype(*this->x)> g2(*this->x);
			{
				this->k = (nk - (*x)->get());
			}
			
			return (this->k);
		}
		
		
		
		K operator[](int i) const
		{
			return get();
		}
		
		K& operator[](int i)
		{
			return this->k;
		}
		
		const K* ptr() const
		{
			return &this->k;
		}
	};
	
	
	
	
	
	
	
	
	QUtils::Multi::Mutexed<X> x;
	x.lock();
	x->set(1);
	x.unlock();
	QUtils::Multi::Mutexed<Y> y(static_cast<QUtils::Multi::Mutexed<X>*>(&x));
	y.lock();
	y->set(1);
	assert_ex(y->get() == 0);
	y.unlock();
	
	auto f1 = [](auto* objPtr, auto arg)
	{
		auto& obj = *objPtr;
		std::lock_guard<decltype(obj)> guard(obj);
		int i = 0;
		auto v = obj->set(arg);
		obj->set(2*arg - v);
		while (obj->get() != arg)
		{
			v = obj->set(arg);
			obj->set(2*arg - v);
			i++;
			if (i > 100000)
			{
				break;
			}
		}
		
		
		
		
		
	};
	
	int v1, v2;
	std::vector<std::thread> threads;
	for (int i = 0; i < 50; i++)
	{
		threads.push_back(std::thread(f1, &y, v1 = (rand() % 100)));
	}
	
	for (int i = 0; i < 50; i++)
	{
		f1(&x, v2 = (rand() % 100));
	}
	
	for (auto& th : threads)
	{
		th.join();
	}
	
	
	x.lock();
	//dout << x->get() << ": " << v2 << "? " << (x->get() == v2) << std::endl;
	assert_ex(x->get() == v2);
	x.unlock();
	y.lock();
	//dout << y->get() << " == " << v1 << "? " << (y->get() == v1) << "\n";
	auto yv = y->get();
	y.unlock();
	
	
	y.lock();
	assert_ex(y[0] == yv);
	y.unlock();
	
	y.lock();
	auto& ykR = y[0];
	static_assert(std::is_same<decltype(y[0]), long double&>::value, "Return type assert failure");
	assert_ex(&ykR == y->ptr());
	const QUtils::Multi::Mutexed<Y>* yP = &y;
	auto ykC = (*yP)[0];
	static_assert(std::is_same<decltype((*yP)[0]), long double>::value, "Return type assert failure");
	assert_ex(ykC == y->get());
	y.unlock();
	
	}
	
	
	
	
	
	
	
	{
		//QUtils::Multi::Task<int, int> t([](auto& x, auto& y){ x.set_value(4); y.set_value(5); });
		QUtils::Multi::Task<int, int, std::promise<int>> t;
		
		auto g = std::get<0>(t.values);
		/*
		t();
		dout << g.get() << "\n";
		assert_ex(g.get() == 4);
		auto g2 = std::get<0>(t.values);
		assert_ex(g.get() == g2.get());
		auto h = std::get<1>(t.values);
		assert_ex(h.get() == 5);*/
	}
	
	/*{
		std::function<void(int&)> f;
		f = [](auto& x) { x = 4; };
		int y = 0;
		f(y);
		assert_ex(y == 4);
	}
	
	{
		std::function<void(int)> f;
		f = [](int k) { auto h = [](auto& x) { x = 4; }; h(k);};
		int y = 0;
		f(y);
		assert_ex(y == 0);
		
		typename QUtils::Multi::Internal::PromiseTypes<int, int, std::promise<int>, std::promise<int>>::type t;
		
		typename QUtils::Multi::Internal::NonPromiseTypes<int, int, std::promise<int>, std::promise<int>>::type t2;
		std::get<1>(t2) = 4;
		//std::get<2>(t2) = 5;
		
	}*/
	
	
	//Result Type Testing
	{
		QUtils::Multi::Result<char, int> r;
		auto& r2 = (QUtils::Multi::Result<char>&)(*(&r));
		r.get() = 4;
		assert_ex(r.get() == 4);
		
		r2.get() = 'z';
		
		static_assert(std::is_same<QUtils::Multi::Result<char>&, decltype(QUtils::Multi::result_cast<1>(r))>::value, "");
		auto& r2_2 = QUtils::Multi::result_cast<1>(r);
		assert_ex(&r2 == &r2_2);
		assert_ex(r2_2.get() == 'z');
		assert_ex(r2.get() == 'z');
	}
	
	
	
	
	
	
	
	
	
	
	//Parallelization Testing
	{
		struct Node
		{
			Node* left;
			Node* right;
			int size = 1;
			unsigned long value = 1;
		};
		
		std::function<Node*(double)> genBranch;
		genBranch = [&genBranch] (double probability) -> Node*
		{
			Node* n = new Node();
			n->left = NULL;
			n->right = NULL;
			n->size = -1;
			if (static_cast<double>(rand())/RAND_MAX < probability)
			{
				n->left = genBranch(probability/2);
			}
			
			if (static_cast<double>(rand())/RAND_MAX < probability)
			{
				n->right = genBranch(probability/2);
			}
			
			return n;
		};
		
		Node* n = genBranch(4);
		dout << n->size << std::endl;
		
		auto j = std::make_shared<QUtils::Multi::AJob<int>>([]() -> int { return 4; });
		QUtils::Multi::AJob<void> j2([](int x) {}, j);
		
		QUtils::Multi::JobFactory<int, Node*> factory([](Node* n)->int {
			n->size = 1;
			if (n->left)
			{
			n->size += n->left->size;
			}
			
			if (n->right)
			{
			n->size += n->right->size;
			}
			
			return n->size;
		});
		
		auto j3 = factory.build(n);
		
		dout << j3->priority() << "\n";
		
		auto j4 = factory.build(n->left);
		j3->depends(j4);
		
		dout << j4->priority() << std::endl;
		
		
		class Tree : public QUtils::Multi::Parallelized
		{
			public:
			Node* root;
			std::vector<Node*> _nodes;
			
			
			static void nodeGo(Node* n, unsigned long v)
			{
				if (!n)
				{
					return;
				}
				n->value += v;
				nodeGo(n->left, n->value);
				nodeGo(n->right, n->value);
				
			}
			
			static void nodeGoMT(Node* n, unsigned long v)
			{
				if (!n)
				{
					return;
				}
				n->value += v;
				nodeGoMT(n->left, n->value);
				nodeGoMT(n->right, n->value);
				
			}
			
			static bool bottomNodes(Node* n, std::vector<Node*>& v)
			{
				if (n == NULL)
				{
					return true;
				}
				
				bool b = bottomNodes(n->left, v);
				bool b2 = bottomNodes(n->right, v);
				if (b && b2)
				{
					v.push_back(n);
				}
				if (n->left == NULL && n->right == NULL)
				{
					//dout << n << " is bottom\n";
				}
				else
				{
					//dout << n << " has left " << n->left << "\n" << n << " has right " << n->right << "\n"; 
				}
				return false;
			}
			
			static std::vector<Node*> bottomNodes(Node* n)
			{
				std::vector<Node*> v;
				if (n == NULL)
				{
					return v;
				}
				
				bool b = n->left == NULL;
				bool b2 = n->right == NULL;
				if (b && b2)
				{
					v.push_back(n);
				}
				if (!b)
				{
					for (auto node : bottomNodes(n->left))
					{
						v.push_back(node);
					}
				}
				if (!b2)
				{
					for (auto node : bottomNodes(n->right))
					{
						v.push_back(node);
					}
				}
				return v;
			}
			
			
			
			public:
			
			const std::vector<Node*>& nodes;
			private:
			Node* genBranch(double probability)
			{
				if (probability < 0)
				{
					probability *= -1;
				}
				Node* n = new Node();
				n->left = NULL;
				n->right = NULL;
				n->size = 1;
				if (static_cast<double>(rand())/RAND_MAX < probability)
				{
					n->left = genBranch(probability/2);
					n->size += n->left->size;
				}
				
				if (static_cast<double>(rand())/RAND_MAX < probability)
				{
					n->right = genBranch(probability/2);
					n->size += n->right->size;
				}
				return n;
			}
			public:
			
			void generate(double prob)
			{
				root = genBranch(prob);
				
				std::function<void(Node*, std::vector<Node*>&)> getNodes;
				getNodes = [&getNodes](Node* n, std::vector<Node*>& v)
				{
					if (n == NULL)
					{
						return;
					}
					v.push_back(n);
					getNodes(n->left, v);
					getNodes(n->right, v);
				};
				getNodes(root, _nodes);
			}
			
			Tree() : Parallelized(4), root(NULL), _nodes(), nodes(_nodes) {}
			Tree(double prob) : Tree()
			{
				generate(prob);
			}
			
			~Tree()
			{
				for (auto node : _nodes)
				{
					delete node;
				}
			}
			
			
			
			void go()
			{
				nodeGo(root, 0);
			}
			
			void goMT()
			{
				auto j = addJob(nodeGoMT, root, 0);
				dout << "Waiting...\n";
				j->wait();
			}
			
			std::vector<Node*> bottom()
			{
				std::vector<Node*> v;
				
				
				
				bottomNodes(root, v);
				//return bottomNodes(root);
				return v;
			}
		};
		
		/*auto pVals = [](Tree& t)
		{
			auto nodes = t.bottom();
			for (auto n : nodes)
			{
				dout << n->value << "\n";
			}
		};*/
		
		auto sVals = [](Tree& t)
		{
			auto nodes = t.bottom();
			unsigned long v = 0;
			for (auto n : nodes)
			{
				v += n->value;
			}
			return v;
		};
		
		const double prob = 1048576;
		Tree t;
		t.generate(prob);
		
		
		dout << "Count: " << t.nodes.size() << std::endl;
		dout << "Bottom Vals: " << sVals(t) << "\n" << std::endl;
		dout << "Gen 1\n";
		t.goMT();
		dout << "Bottom Vals: " << sVals(t) << "\n";
		dout << "Gen 2\n";
		t.go();
		dout << "Bottom Vals: " << sVals(t) << "\n";
		
		dout << "\n\nGenerating mutexed tree\n";
		QUtils::Multi::Mutexed<Tree> mutTree;
		mutTree.run<double>(&Tree::generate, prob);
		
		mutTree.lock();
		dout << "Count: " << mutTree->nodes.size() << std::endl;
		dout << "Bottom Vals: " << sVals(*mutTree) << "\n" << std::endl;
		mutTree.unlock();
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return true;
}