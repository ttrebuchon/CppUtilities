#pragma once
#include <exception>
#include <string>
namespace QUtils { namespace Testing {
	
class AssertionFailedException : public std::exception
{
	protected:
	std::string _file;
	int _line;
	std::string _func;
	std::string _what;
	const char* _whatC;
	constexpr static const auto className = "AssertionFailedException";
	std::string _message;
	std::exception_ptr _inner;
	
	public:
	AssertionFailedException(std::string _file, int _line, std::string _func, std::string exp) : 
	_file(_file),
	_line(_line),
	_func(_func),
	_what(""),
	_whatC(NULL),
	_message(exp),
	_inner(nullptr)
	{ }
	
	
	AssertionFailedException(std::exception_ptr ex, std::string comment = "") : _file(""), _line(-1), _func(""), _what(""), _whatC(NULL), _message(comment), _inner(ex) {}
	
	
	
	const char* what() const noexcept override {
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
		if (file() != "")
		{
			_what += file();
		}
		if (file() != "" && line() != -1)
		{
			_what += ":";
		}
		if (line() != -1)
		{
			_what += "L" + std::to_string(line());
		}
		if ((file() != "" || line() != -1) && func() != "")
		{
			_what += ":";
		}
		if (func() != "")
		{
			_what += func();
		}
		if (file() != "" || line() != -1 || func() != "")
		{
			_what += "::";
		}
		_what += className;
		if (message() != "")
		{
			_what += "::Assertion Failed: '" + message() + "'";
		}
		if (inner())
		{
			try
			{
				std::rethrow_exception(inner());
			}
			catch (const std::exception& ex)
			{
				_what += "\n::Inner Exception->";
				_what += ex.what();
			}
		}
		_whatC = _what.c_str();
	}
	}
	
	
	
	AssertionFailedException& Msg(std::string s)
	{
		this->_message = s;
		return *this;
	}
	AssertionFailedException& File(std::string s)
	{
		this->_file = s;
		return *this;
	}
	AssertionFailedException& Function(std::string s)
	{
		this->_func = s;
		return *this;
	}
	AssertionFailedException& Line(int i)
	{
		this->_line = i;
		return *this;
	}
	
	
	virtual std::string message() const
	{
		return _message;
	}
	
	virtual const std::exception_ptr inner() const
	{
		return _inner;
	}
	
	virtual int line() const
	{
		return _line;
	}
	
	virtual std::string file() const
	{
		return _file;
	}
	
	virtual std::string func() const
	{
		return _func;
	}
	
	};
}
}

#define assert_ex(x) (( x ) ? true : throw QUtils::Testing::AssertionFailedException(__FILE__, __LINE__, __func__, #x))