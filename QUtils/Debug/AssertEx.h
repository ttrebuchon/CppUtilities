#pragma once
#include <exception>
#include <sstream>

namespace QUtils { namespace Debug {
	
class AssertionFailedException : public std::exception
{
	protected:
	std::string file;
	int line;
	std::string func;
	std::string _what;
	const char* _whatC;
	const std::string className = "AssertionFailedException";
	std::string message;
	std::exception_ptr inner;
	
	public:
	AssertionFailedException(std::string file, int line, std::string func) : file(file), line(line), func(func), _what(""), _whatC(NULL), message(""), inner(nullptr)
	{
		
	}
	
	AssertionFailedException(std::string file) : AssertionFailedException(file, -1, "") 
	{
		
	} 
	
	AssertionFailedException(int line) : AssertionFailedException("", line, "")
	{
		
	}
	
	AssertionFailedException(std::string file, int line) : AssertionFailedException(file, line, "") 
	{
		
	}
	
	AssertionFailedException(int line, std::string func) : AssertionFailedException("", line, func)
	{
		
	}
	
	AssertionFailedException(std::string file, std::string func) : AssertionFailedException(file, -1, func)
	{
		
	}
	
	AssertionFailedException() : AssertionFailedException("", -1, "")
	{
		
	}
	AssertionFailedException(std::exception_ptr ex, std::string comment = "") : file(""), line(-1), func(""), _what(""), _whatC(NULL), message(comment), inner(ex)
	{
		
	}
	
	
	
	const char* what() const noexcept override
	{
	if (_whatC == NULL)
	{
		((AssertionFailedException*)this)->build();
	}
	    return _whatC;
	}
	
	virtual void build()
	{
		if (_what == "")
		{
		_what = "Assertion Failed";
	    if (_what == "")
	    {
	    	_what = className;
	    }
	    
		std::stringstream ss;
		if (file != "")
		{
			ss << "" << file;
		}
		
		if (file != "" && line != -1)
		{
			ss << ":";
		}
		
		if (line != -1)
		{
			ss << "L" << line;
		}
		
		if ((file != "" || line != -1) && func != "")
		{
			ss << ":";
		}
		
		if (func != "")
		{
			ss << func;
		}
		
		if (file != "" || line != -1 || func != "")
		{
			ss << "::";
		}
		
		ss << _what;
		if (message != "")
		{
			ss << "::" << message;
		}
		
		if (inner)
		{
			try
			{
				std::rethrow_exception(inner);
			}
			catch (const std::exception& ex)
			{
				ss << "\n::Inner Exception->" << ex.what();
			}
		}
		
		_what = ss.str();
		_whatC = _what.c_str();
	}
	}
	
	
	
	AssertionFailedException& Msg(std::string s)
	{
		this->message = s; 
		return *this; 
	}
	
	AssertionFailedException & File(std::string s) 
	{ 
		this->file = s; 
		return *this; 
	}
	
	AssertionFailedException & Function(std::string s) 
	{ 
		this->func = s; 
		return *this; 
	}
	
	AssertionFailedException& Line(int i) 
	{ 
		this->line = i; 
		return *this; 
	} 
	
	
};

namespace Helpers
{
	bool AssertionFailedCaller(auto file, auto line, auto func, auto expr)
	{
		throw AssertionFailedException().Line(line).Function(func).Msg(expr).File(file);
	}
}

}
}

#define assert_ex(x) (( x ) ? true : ::QUtils::Debug::Helpers::AssertionFailedCaller(__FILE__, __LINE__, __FUNCTION__, #x))