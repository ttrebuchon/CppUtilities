#pragma once

#include <iostream>
#include <list>


namespace QUtils::Output
{
	
	
	class MultiBuf : public std::streambuf
	{
		protected:
		std::list<std::streambuf*> bufs;
		public:
		MultiBuf();
		
		void push(std::streambuf* buf);
		
		
		virtual void imbue(const std::locale& loc) override;
		virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) override;
		
		virtual int sync() override;
		
		virtual std::streamsize xsputn(const char* s, std::streamsize n) override;
		
		virtual int overflow(int c = EOF) override;
	};
	
	class MultiStream : public std::ostream
	{
		protected:
		
		public:
		MultiStream();
		
		virtual ~MultiStream();
		
		virtual void add(std::ostream&);
		
	};
	
	
}