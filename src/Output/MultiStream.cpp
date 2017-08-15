#include <QUtils/Output/MultiStream.h>

#include <QUtils/Exception/Exception.h>


namespace QUtils::Output
{
	QUTILS_CUSTOM_EXCEPTION(MultiBufException,);
	
	
	MultiBuf::MultiBuf() : std::streambuf(), bufs()
	{
		
	}
	
	void MultiBuf::push(std::streambuf* buf)
	{
		if (buf == this)
		{
			throw MultiBufException().Function(__func__).Line(__LINE__).Msg("Can not put a MultiBuf inside itself");
		}
		bufs.push_back(buf);
	}
	
	void MultiBuf::imbue(const std::locale& loc)
	{
		for (auto buf : bufs)
		{
			buf->pubimbue(loc);
		}
	}
	
	std::streampos MultiBuf::seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which)
	{
		return bufs.front()->pubseekoff(off, way, which);
	}
	
	int MultiBuf::sync()
	{
		int res = 0;
		for (auto buf : bufs)
		{
			if (res == 0)
			{
				res = buf->pubsync();
			}
			else
			{
				buf->pubsync();
			}
		}
		return res;
	}
	
	
	
	
	std::streamsize MultiBuf::xsputn(const char* s, std::streamsize n)
	{
		std::streamsize size = 0;
		for (auto buf : bufs)
		{
			size = buf->sputn(s, n);
		}
		return size;
	}
	
	int MultiBuf::overflow(int c)
	{
		if (c == EOF)
		{
			return !EOF;
		}
		else
		{
			bool v = false;
			
			for (auto buf : bufs)
			{
				v = v || buf->sputc(c) == EOF;
			}
			if (v)
			{
				return EOF;
			}
			else
			{
				return c;
			}
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	MultiStream::MultiStream() : std::ostream(new MultiBuf())
	{
		
	}
	
	MultiStream::~MultiStream()
	{
		
	}
	
	
	void MultiStream::add(std::ostream& os)
	{
		((MultiBuf*)this->rdbuf())->push(os.rdbuf());
	}
}