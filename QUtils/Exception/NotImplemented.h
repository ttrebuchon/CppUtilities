#pragma once

#ifdef DEBUG

#include <exception>
#include <sstream>


class NotImplementedException : public std::exception
{
	protected:
	std::string file;
	int line;
	std::string func;
	std::string _what;
	const char* _whatC;
	const std::string className = "NotImplementedException";
	std::string message;
	std::exception_ptr inner;
	
	public:
	NotImplementedException(std::string file, int line, std::string func) : file(file), line(line), func(func), _what(""), _whatC(NULL), message(""), inner(nullptr)
	{
		
	}
	
	NotImplementedException(std::string file) : NotImplementedException(file, -1, "") 
	{
		
	} 
	
	NotImplementedException(int line) : NotImplementedException("", line, "")
	{
		
	}
	
	NotImplementedException(std::string file, int line) : NotImplementedException(file, line, "") 
	{
		
	}
	
	NotImplementedException(int line, std::string func) : NotImplementedException("", line, func)
	{
		
	}
	
	NotImplementedException(std::string file, std::string func) : NotImplementedException(file, -1, func)
	{
		
	}
	
	NotImplementedException() : NotImplementedException("", -1, "")
	{
		
	}
	NotImplementedException(std::exception_ptr ex, std::string comment = "") : file(""), line(-1), func(""), _what(""), _whatC(NULL), message(comment), inner(ex)
	{
		
	}
	
	
	
	const char* what() const noexcept override
	{
	if (_whatC == NULL)
	{
		((NotImplementedException*)this)->build();
	}
	    return _whatC;
	}
	
	virtual void build()
	{
		if (_what == "")
		{
		_what = "This has not been implemented";
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
	
	
	
	NotImplementedException& Msg(std::string s)
	{
		this->message = s; 
		return *this; 
	}
	
	NotImplementedException & File(std::string s) 
	{ 
		this->file = s; 
		return *this; 
	}
	
	NotImplementedException & Function(std::string s) 
	{ 
		this->func = s; 
		return *this; 
	}
	
	NotImplementedException& Line(int i) 
	{ 
		this->line = i; 
		return *this; 
	} 
	
	
};


#define NotImp() (NotImplementedException("", __func__).Line(__LINE__).File(__FILE__))
#endif