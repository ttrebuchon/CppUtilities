#include <QUtils/GUI/SDL/StreamLabelViewComponent.h>
#include <QUtils/GUI/Errors.h>

#include <QUtils/Output/MultiStream.h>

#include <future>


namespace QUtils::GUI::SDL
{
	typedef typename SDLStreamLabelViewComponent::Buf Buf_t;
	
	Buf_t::Buf(SDLStreamLabelViewComponent* label) : std::basic_stringbuf<char>(), label(label)
	{
		
	}
	
	std::streambuf* Buf_t::setbuf(char* c, std::streamsize n)
	{
		std::basic_stringbuf<char>::setbuf(c, n);
		label->setTextChanged();
		
		return this;
	}
	
	int Buf_t::sync()
	{
		auto val = std::basic_stringbuf<char>::sync();
		label->setTextChanged();
		return val;
	}
	
	std::streamsize Buf_t::xsputn(const char* s, std::streamsize n)
	{
		return std::basic_stringbuf<char>::xsputn(s, n);
	}
	
	int Buf_t::overflow(int c)
	{
		return std::basic_stringbuf<char>::overflow(c);
	}
	
	std::string Buf_t::str() const
	{
		return std::basic_stringbuf<char>::str();
	}
	
	void Buf_t::str(const std::string& value)
	{
		std::basic_stringbuf<char>::str(value);
		label->setTextChanged();
	}
	
	
	
	
	
	
	
	
	
	
	
	SDLStreamLabelViewComponent::SDLStreamLabelViewComponent(const std::string id, bool touch, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(id, touch, font, fontSize), _buf(new Buf_t(this))
	{
		
	}
	
	SDLStreamLabelViewComponent::SDLStreamLabelViewComponent(bool touch, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(touch, font, fontSize), _buf(new Buf_t(this))
	{
		
	}
	
	SDLStreamLabelViewComponent::SDLStreamLabelViewComponent(const std::string id, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(id, font, fontSize), _buf(new Buf_t(this))
	{
		
	}
	SDLStreamLabelViewComponent::SDLStreamLabelViewComponent(std::ostream& stream, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(font, fontSize), _buf(new Buf_t(this))
	{
		
	}
	
	SDLStreamLabelViewComponent::~SDLStreamLabelViewComponent()
	{
		
	}
	
	
	
	
	
	
	
	void SDLStreamLabelViewComponent::setTextChanged()
	{
		_textChanged = true;
	}
	
	
	void SDLStreamLabelViewComponent::setTextChangedAsync()
	{
		
		std::async(std::launch::async, [&]()
		{
			_textChanged = true;
		});
	}
	
	
	
	
	
	
	
		
	std::string SDLStreamLabelViewComponent::text() const
	{
		return _buf->str();
	}
	
	QUTILS_CUSTOM_EXCEPTION(StreamTextException, );
	
	void SDLStreamLabelViewComponent::text(const std::string value)
	{
		if (value != "")
		{
			throw StreamTextException().Msg("Can't set text of stream label!");
		}
		std::lock_guard<std::recursive_mutex> lock(this_m);
		_buf->str(value);
		setTextChanged();
	}
	
	void SDLStreamLabelViewComponent::clear()
	{
		this->text("");
	}
	
	Buf_t* SDLStreamLabelViewComponent::buf()
	{
		return _buf;
	}
	
	const Buf_t* SDLStreamLabelViewComponent::buf() const
	{
		return _buf;
	}
	
}