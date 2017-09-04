#ifndef INCLUDED_UTIL_EXCEPTION_H
#define INCLUDED_UTIL_EXCEPTION_H

#include <exception>
#include <sstream>


	#define QUTILS_CUSTOM_EXCEPTION(name, msg) class name : public std::exception { \
	protected: \
	std::string file; \
	int line; \
	std::string func; \
	std::string _what; \
	const char* _whatC; \
	const std::string className = #name; \
	std::string message; \
	std::exception_ptr inner; \
	\
	public: \
	name(std::string file, int line, std::string func) : file(file), line(line), func(func), _what(""), _whatC(NULL), message(""), inner(nullptr) \
	{  } \
	\
	name(std::string file) : name(file, -1, "") \
	{ } \
	\
	name(int line) : name("", line, "") \
	{ } \
	\
	name(std::string file, int line) : name(file, line, "") \
	{ } \
	\
	name(int line, std::string func) : name("", line, func) \
	{ } \
	\
	name(std::string file, std::string func) : name(file, -1, func) \
	{ } \
	\
	name() : name("", -1, "") \
	{ } \
	\
	\
	name(std::exception_ptr ex, std::string comment = "") : file(""), line(-1), func(""), _what(""), _whatC(NULL), message(comment), inner(ex) {} \
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
		if (file != "") \
		{ \
			ss << "" << file; \
		} \
		if (file != "" && line != -1) \
		{ \
			ss << ":"; \
		} \
		if (line != -1) \
		{ \
			ss << "L" << line; \
		} \
		if ((file != "" || line != -1) && func != "") \
		{ \
			ss << ":"; \
		} \
		if (func != "") \
		{ \
			ss << func; \
		} \
		if (file != "" || line != -1 || func != "") \
		{ \
			ss << "::"; \
		} \
		ss << _what; \
		if (message != "") \
		{ \
			ss << "::" << message; \
		} \
		if (inner) \
		{ \
			try \
			{ \
				std::rethrow_exception(inner); \
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
		this->message = s; \
		return *this; \
	} \
	name & File(std::string s) \
	{ \
		this->file = s; \
		return *this; \
	} \
	name & Function(std::string s) \
	{ \
		this->func = s; \
		return *this; \
	} \
	name & Line(int i) \
	{ \
		this->line = i; \
		return *this; \
	} \
	\
	\
	}
	
	#define UTIL_CUSTOM_EXCEPTION(name, msg) QUTILS_CUSTOM_EXCEPTION(name, msg)


#endif
	