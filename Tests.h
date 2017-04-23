#ifndef INCLUDED_UTIL_TESTS_H
#define INCLUDED_UTIL_TESTS_H

#include <iostream>
#include <exception>
#include <sstream>

using std::cout;
using std::endl;

class StringException : public std::exception
{
	private:
	std::string msg;
	
	public:
	StringException(std::string str) : msg(str) {}
	
	const char* what() const noexcept override
	{
		return msg.c_str();
	}
};

#define assert_ex(x) ( x ) ? NULL : throw StringException((std::stringstream() << __FILE__ << ":L" << __LINE__ << "::Assertion Failed: " << #x).str())

class Testing
{
	public:
	
	static void run();
	
	static bool Func();
	static bool NNST();
	static bool CustomException();
	static bool Markov();
	static bool Stopwatch();
	static bool String();
	static bool Math();
};





class DebugOut
{
	public:
	static std::ostream*& nOut() {
		static std::ostream* o = new std::ostream(new NullBuffer());
		return o;
	}
	
	static std::ostream*& rOut() {
		static std::ostream* o = &std::cerr;
		return o;
	}
	
	class NullBuffer : public std::streambuf
	{
		public:
		int overflow(int c)
		{
			return c;
		}
	};
	
	public:
	
	static bool& enabled() {
		static bool b = 
		#ifdef DEBUG
		true;
		#else
		false;
		#endif
		return b;
	}
	
	static std::ostream& Out()
	{
		if (enabled())
		{
			return *rOut();
		}
		else
		{
			return *nOut();
		}
	}
	
	
	
};

#define dout DebugOut::Out()




#endif