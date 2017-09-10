#pragma once

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

std::string __assert_ex_helper(auto file, auto line, auto msg)
{
	std::stringstream ss;
	ss << file << ":L" << line << "::Assertion Failed: " << msg;
	return ss.str();
}

//#define assert_ex(x) ( x ) ? NULL : throw StringException(static_cast<std::stringstream>(std::stringstream() << __FILE__ << ":L" << __LINE__ << "::Assertion Failed: " << #x).str())

bool _stringException_caller(auto file, auto line, auto exp)
{
	throw StringException(__assert_ex_helper(file, line, exp));
	return false;
	
}

#define assert_ex(x) (( x ) ? true : _stringException_caller(__FILE__, __LINE__, #x))

#define assert_not_reached() _stringException_caller(__FILE__, __LINE__, "Not a valid test path!")



class DebugOut
{
	public:
	static std::ostream*& nOut() {
		static std::ostream* o = new std::ostream(new NullBuffer());
		return o;
	}
	
	static std::ostream*& rOut() {
		static std::ostream* o = &std::cout;
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

extern std::stringstream dout_ss;