#ifndef INCLUDED_UTIL_EXCEPTION_H
#define INCLUDED_UTIL_EXCEPTION_H

#include <exception>
#include <sstream>


	#define QUTILS_CUSTOM_EXCEPTION(name, msg) class name : public std::exception { \
	protected: \
	std::string _file; \
	int _line; \
	std::string _func; \
	std::string _what; \
	const char* _whatC; \
	const std::string className = #name; \
	std::string _message; \
	std::exception_ptr _inner; \
	\
	public: \
	name(std::string _file, int _line, std::string _func) : _file(_file), _line(_line), _func(_func), _what(""), _whatC(NULL), _message(""), _inner(nullptr) \
	{  } \
	\
	name(std::string _file) : name(_file, -1, "") \
	{ } \
	\
	name(int _line) : name("", _line, "") \
	{ } \
	\
	name(std::string _file, int _line) : name(_file, _line, "") \
	{ } \
	\
	name(int _line, std::string _func) : name("", _line, _func) \
	{ } \
	\
	name(std::string _file, std::string _func) : name(_file, -1, _func) \
	{ } \
	\
	name() : name("", -1, "") \
	{ } \
	\
	\
	name(std::exception_ptr ex, std::string comment = "") : _file(""), _line(-1), _func(""), _what(""), _whatC(NULL), _message(comment), _inner(ex) {} \
	\
	\
	\
	const char* what() const noexcept override { \
	if (_whatC == NULL) \
	{ \
		((name*)this)->build(); \
	} \
	    return _whatC; \
	}\
	\
	virtual void build() { \
	if (_what == "") \
	{ \
	    _what = #msg; \
	    if (_what == "") \
	    { \
	    	_what = className; \
	    } \
		std::stringstream ss; \
		if (file() != "") \
		{ \
			ss << "" << file(); \
		} \
		if (file() != "" && line() != -1) \
		{ \
			ss << ":"; \
		} \
		if (line() != -1) \
		{ \
			ss << "L" << line(); \
		} \
		if ((file() != "" || line() != -1) && func() != "") \
		{ \
			ss << ":"; \
		} \
		if (func() != "") \
		{ \
			ss << func(); \
		} \
		if (file() != "" || line() != -1 || func() != "") \
		{ \
			ss << "::"; \
		} \
		ss << _what; \
		if (message() != "") \
		{ \
			ss << "::" << message(); \
		} \
		if (inner()) \
		{ \
			try \
			{ \
				std::rethrow_exception(inner()); \
			} \
			catch (const std::exception& ex) \
			{ \
				ss << "\n::Inner Exception->" << ex.what(); \
			} \
		} \
		_what = ss.str(); \
		_whatC = _what.c_str(); \
	} \
	} \
	\
	\
	\
	name & Msg(std::string s) \
	{ \
		this->_message = s; \
		return *this; \
	} \
	name & File(std::string s) \
	{ \
		this->_file = s; \
		return *this; \
	} \
	name & Function(std::string s) \
	{ \
		this->_func = s; \
		return *this; \
	} \
	name & Line(int i) \
	{ \
		this->_line = i; \
		return *this; \
	} \
	\
	\
	virtual std::string message() const \
	{ \
		return _message; \
	} \
	\
	virtual const std::exception_ptr inner() const \
	{ \
		return _inner; \
	} \
	\
	virtual int line() const \
	{ \
		return _line; \
	} \
	\
	virtual std::string file() const \
	{ \
		return _file; \
	} \
	\
	virtual std::string func() const \
	{ \
		return _func; \
	} \
	\
	}
	
	#define UTIL_CUSTOM_EXCEPTION(name, msg) QUTILS_CUSTOM_EXCEPTION(name, msg)


#endif
	