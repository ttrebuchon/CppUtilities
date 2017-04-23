#ifndef INCLUDED_UTIL_EXCEPTION_H
#define INCLUDED_UTIL_EXCEPTION_H

#include <exception>
#include <sstream>


	#define UTIL_CUSTOM_EXCEPTION(name, msg) class name : public std::exception { \
	std::string file; \
	int line; \
	std::string func; \
	std::string _what; \
	const char* _whatC; \
	\
	public: \
	name(std::string file, int line, std::string func) : file(file), line(line), func(func), _what(""), _whatC(NULL) \
	{ build(); } \
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
	\
	\
	const char* what() const noexcept override { \
	    return _whatC; \
	}\
	\
	void build() { \
	if (_what == "") \
	{ \
	    std::string message = #msg; \
		std::stringstream ss; \
		if (file != "") \
		{ \
			ss << "" << __FILE__; \
		} \
		if (file != "" && line != -1) \
		{ \
			ss << ":"; \
		} \
		if (line != -1) \
		{ \
			ss << "L" << __LINE__; \
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
		ss << message; \
		_what = ss.str(); \
		_whatC = _what.c_str(); \
	} \
	} \
	\
	\
	}

#endif
	