#pragma once



#include <exception>
#include <sstream>


class ArgumentOutOfRangeException : public std::exception
{
	protected:
	std::string file;
	int line;
	std::string func;
	std::string _what;
	const char* _whatC;
	const std::string className = "ArgumentOutOfRangeException";
	std::string message;
	std::exception_ptr inner;
	
	public:
	ArgumentOutOfRangeException(std::string file, int line, std::string func) : file(file), line(line), func(func), _what(""), _whatC(NULL), message(""), inner(nullptr)
	{
		
	}
	
	ArgumentOutOfRangeException(std::string file) : ArgumentOutOfRangeException(file, -1, "") 
	{
		
	} 
	
	ArgumentOutOfRangeException(int line) : ArgumentOutOfRangeException("", line, "")
	{
		
	}
	
	ArgumentOutOfRangeException(std::string file, int line) : ArgumentOutOfRangeException(file, line, "") 
	{
		
	}
	
	ArgumentOutOfRangeException(int line, std::string func) : ArgumentOutOfRangeException("", line, func)
	{
		
	}
	
	ArgumentOutOfRangeException(std::string file, std::string func) : ArgumentOutOfRangeException(file, -1, func)
	{
		
	}
	
	ArgumentOutOfRangeException() : ArgumentOutOfRangeException("", -1, "")
	{
		
	}
	ArgumentOutOfRangeException(std::exception_ptr ex, std::string comment = "") : file(""), line(-1), func(""), _what(""), _whatC(NULL), message(comment), inner(ex)
	{
		
	}
	
	
	
	const char* what() const noexcept override
	{
	if (_whatC == NULL)
	{
		((ArgumentOutOfRangeException*)this)->build();
	}
	    return _whatC;
	}
	
	virtual void build()
	{
		if (_what == "")
		{
		_what = "The argument is out of range";
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
	
	
	
	ArgumentOutOfRangeException& Msg(std::string s)
	{
		this->message = s; 
		return *this; 
	}
	
	ArgumentOutOfRangeException & File(std::string s) 
	{ 
		this->file = s; 
		return *this; 
	}
	
	ArgumentOutOfRangeException & Function(std::string s) 
	{ 
		this->func = s; 
		return *this; 
	}
	
	ArgumentOutOfRangeException& Line(int i) 
	{ 
		this->line = i; 
		return *this; 
	} 
	
	
};


#define ArgOutOfRange() (ArgumentOutOfRangeException("", __func__).Line(__LINE__).File(__FILE__))