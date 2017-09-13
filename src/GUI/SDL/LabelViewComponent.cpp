#include <QUtils/GUI/SDL/LabelViewComponent.h>
#include <QUtils/Drawing/SDL/Font.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/SDL/RenderTarget.h>
#include <QUtils/GUI/Errors.h>
#include <QUtils/String/String.h>

#include <QUtils/Exception/NotImplemented.h>
#include <iostream>
#include <assert.h>


namespace QUtils::GUI::SDL
{
	namespace Internal
	{
		TextSegment::TextSegment() : texture(NULL), surface(NULL), lastCheckSum(0), start(0), end(0)
		{
			
		}
		
		TextSegment::~TextSegment()
		{
			if (texture != NULL)
			{
				delete texture;
				texture = NULL;
			}
			
			if (surface != NULL)
			{
				delete surface;
				surface = NULL;
			}
		}
		
		#define CHKSUM_MULT_RANGE 5
		
		unsigned long int calcCheckSum(const std::string str, unsigned int start, unsigned int end)
		{
			if (str.length() <= 0)
			{
				return 0;
			}
			auto disp = start;
			unsigned long sum = 0;
			for (int i = 0; i + disp <= end; ++i)
			{
				sum += ((int)str[i + disp])*((i%CHKSUM_MULT_RANGE)+1);
			}
			return sum;
		}
	}
	
	
	
	
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string id, bool touch, const std::string font, unsigned int fontSize) : TextViewComponent(id, touch), lastW(-1), lastH(-1), lastNativeW(-1), lastNativeH(-1), _fontNameChanged(true), _fontSizeChanged(true), segments(), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1), lastStringCheckSum(0)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::SDLLabelViewComponent(bool touch, const std::string font, unsigned int fontSize) : TextViewComponent(touch), lastW(-1), lastH(-1), lastNativeW(-1), lastNativeH(-1), _fontNameChanged(true), _fontSizeChanged(true), segments(), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1), lastStringCheckSum(0)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string id, const std::string font, unsigned int fontSize) : TextViewComponent(id), lastW(-1), lastH(-1), lastNativeW(-1), lastNativeH(-1), _fontNameChanged(true), _fontSizeChanged(true), segments(), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1), lastStringCheckSum(0)
	{
		_changed = true;
	}
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string font, unsigned int fontSize) : TextViewComponent(), lastW(-1), lastH(-1), lastNativeW(-1), lastNativeH(-1), _fontNameChanged(true), _fontSizeChanged(true), segments(), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1), lastStringCheckSum(0)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::~SDLLabelViewComponent()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (texture != NULL)
		{
			delete texture;
			texture = NULL;
		}
		
		for (auto segment : segments)
		{
			delete segment;
		}
		segments.clear();
		
		if (lastString != NULL)
		{
			delete lastString;
			lastString = NULL;
		}
	}
		
	void SDLLabelViewComponent::update()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (changed())
		{
			std::cerr << "Updating (_textChanged = " << _textChanged << ")\n";
			onUpdate(this);
			if (_fontNameChanged || _fontSizeChanged)
			{
			_font = SDLFontResourceLoader::get(_fontName, _fontSize);
			_fontNameChanged = _fontSizeChanged = false;
			resetSegments();
			}
			if (texture != NULL)
			{
				std::cerr << "Deleting texture...\n";
				delete texture;
				texture = NULL;
			}
			_changed = false;
			lastNativeW = lastNativeH = -1;
			_textChanged = false;
			updateTextures();
		}
	}
	
	void SDLLabelViewComponent::render(RenderTarget* genericTarget, int x, int y, int w, int h)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		auto sdlTarget = dynamic_cast<SDLRenderTarget*>(genericTarget);
		if (sdlTarget == NULL)
		{
			throw IncompatibleGUI_TypeException().Msg("RenderTarget isn't an SDLRenderTarget").File(__FILE__).Function(__func__);
		}
		auto ren = sdlTarget->getRenderer();
		
		int tmpW = w;
		int tmpH = h;
		calcRenderDimensions(tmpW, tmpH);
		w = tmpW;
		h = tmpH;
		
		for (auto segment : segments)
		{
			if (segment->texture == NULL && segment->surface != NULL)
			{
				try
				{
				segment->texture = segment->surface->createTexture(ren);
				}
				catch (Drawing::SDL::SDLErrorException& ex)
				{
					std::cerr << "(" << std::flush << segment->surface->width() << ", " << segment->surface->height() << ")\t[" << segment->end - segment->start << "]\n";
					throw;
				}
				delete segment->surface;
				segment->surface = NULL;
			}
		}
		
		if (w != lastW || h != lastH || (texture == NULL && wrapWidth() <= 0) || _textChanged)
		{
			std::cerr << "(" << w << ", " << lastW << ", " << h << ", " << lastH << ", " << texture << ", " << _textChanged << ")\n";
			std::cerr << "Creating surface...\n" << std::flush;
			lastW = w;
			lastH = h;
			if (texture != NULL)
			{
				delete texture;
				texture = NULL;
			}
			
			Drawing::SDL::Surface* surf = NULL;
			auto wrapW = wrapWidth();
			
			_textChanged = false;
			auto text = QUtils::String(this->text()).replace("\r\n", "\n");
			try
			{
			if (wrapW > 0)
			{
			
			/*surf = _font->surfaceBlendedWrapped(text, (Drawing::SDL::Color)color(), wrapW);
			w = lastNativeW = surf->width();
			h = lastNativeH = surf->height();*/
			}
			else
			{
			surf = _font->surfaceBlended(text, (Drawing::SDL::Color)color());
			lastNativeW = surf->width();
			lastNativeH = surf->height();
			}
			}
			catch (Drawing::SDL::SDLErrorException& ex)
			{
				if (ex.message() == "SDL Error: Text has zero width" && text.length() == 0)
				{
					lastNativeW = lastNativeH = 0;
					return;
				}
				else
				{
					throw RenderException(std::current_exception()).Line(__LINE__).Function(__func__);
				}
			}
			catch (...)
			{
				throw RenderException(std::current_exception()).Line(__LINE__).Function(__func__);
			}
			
			
			
			if (height() == -2)
			{
				h = (int)(static_cast<double>(surf->height())/surf->width()*w);
			}
			
			if (surf != NULL)
			{
			
			texture = surf->createTexture(ren);
			
			delete surf;
			}
			
			
			
		}
		
		if (texture == NULL)
		{
		
		int dy = 0;
		
		for (auto s : segments)
		{
			s->texture->alphaMod(static_cast<unsigned char>(255*opacity()));
			s->texture->blendMode(Drawing::SDL::BlendMode::Blend);
			ren->copy(s->texture, NULL, {x, y+dy, static_cast<int>(static_cast<double>(s->texture->width())/lastNativeW*w), static_cast<int>(static_cast<double>(s->texture->height())/lastNativeH*h)});
			dy += s->texture->height();
			
			
		}
		}
		else
		{
			texture->alphaMod(static_cast<unsigned char>(255*opacity()));
		texture->blendMode(Drawing::SDL::BlendMode::Blend);
		ren->copy(texture, NULL, {x, y, w, h});
		}
		
		
	}
	
	int SDLLabelViewComponent::nativeWidth() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (lastNativeW < 0 || lastNativeH < 0)
		{
			updateNativeDims();
		}
		return lastNativeW;
	}
	
	int SDLLabelViewComponent::nativeHeight() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (lastNativeW < 0 || lastNativeH < 0)
		{
			updateNativeDims();
		}
		return lastNativeH;
	}
	
	double SDLLabelViewComponent::wrapWidth() const
	{
		return _wrapWidth;
	}
	
	void SDLLabelViewComponent::wrapWidth(const double value)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (value != _wrapWidth)
		{
			_changed = true;
			_wrapWidth = value;
		}
	}
	
	void SDLLabelViewComponent::calcRelativeDimensions(double& outW, double& outH) const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		auto tmpW = width();
		auto tmpH = height();
		
		if (tmpW == -2 && tmpH == -2)
		{
			tmpW = tmpH = -1;
		}
		
		double nativeW, nativeH;
		
		if (tmpW < 0 || tmpH < 0)
		{
			if (lastNativeW < 0 || lastNativeH < 0)
			{
				updateNativeDims();
			}
			nativeW = lastNativeW;
			nativeH = lastNativeH;
		}
		
		if (tmpW >= 0)
		{
			outW = tmpW;
		}
		else if (tmpW == -1)
		{
			outW = nativeW/outW;
		}
		
		if (tmpH >= 0)
		{
			outH = tmpH;
		}
		else if (tmpH == -1)
		{
			outH = nativeH/outH;
		}
		
		
		
		if (tmpW == -2)
		{
			outW *= nativeW/nativeH;
		}
		
		if (tmpH == -2)
		{
			outH *= nativeH/nativeW;
		}
	}
	
	void SDLLabelViewComponent::updateNativeDims() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (_font == NULL || changed())
		{
			const_cast<SDLLabelViewComponent*>(this)->update();
		}
		if (wrapWidth() <= 0)
		{
			_font->sizeText(QUtils::String(this->text()).replace("\r\n", "\n"), &lastNativeW, &lastNativeH);
		}
		else
		{
			Drawing::SDL::Surface* surf = NULL;
			lastNativeH = 0;
			lastNativeW = 0;
			int w, h;
			for (auto segment : segments)
			{
				if (segment->texture == NULL)
				{
					w = segment->surface->width();
					h = segment->surface->height();
				}
				else
				{
					w = segment->texture->width();
					h = segment->texture->height();
				}
				
				lastNativeW = std::max(w, lastNativeW);
				lastNativeH += h;
			}
			/*
			try
			{
			auto text = QUtils::String(this->text()).replace("\r\n", "\n");
			surf = _font->surfaceBlendedWrapped(text, (Drawing::SDL::Color)color(), wrapWidth());
			lastNativeH = surf->height();
			lastNativeW = surf->width();
			delete surf;
			}
			catch (Drawing::SDL::SDLErrorException& ex)
			{
				if (surf != NULL)
				{
					delete surf;
				}
				if (ex.message() == "SDL Error: Text has zero width")
				{
					lastNativeW = lastNativeH = 0;
				}
				else
				{
					throw RenderException(std::current_exception()).Line(__LINE__).Function(__func__);
				}
			}
			catch (...)
			{
				if (surf != NULL)
				{
					delete surf;
				}
				throw RenderException(std::current_exception()).Line(__LINE__).Function(__func__);
			}*/
		}
	}
	
	std::list<unsigned int> SDLLabelViewComponent::splitString(std::string str) const
	{
		std::list<unsigned int> splits;
		if (wrapWidth() <= 0)
		{
			return splits;
		}
		
		const int divider = 30;
		
		/*for (int i = divider; i < str.length()-1; i += divider)
		{
			splits.push_back(i);
		}
		
		return splits;*/
		
		
		auto findClosest = [&str](std::size_t index, std::size_t last) -> long
		{
			std::size_t negIndex = index, posIndex = index;
			bool hitLeft = false, hitRight = false;
			while (!hitLeft || !hitRight)
			{
				if (negIndex <= last)
				{
					hitLeft = true;
				}
				else
				{
					if (str[negIndex] == ' ' || str[negIndex] == '\n')
					{
						return negIndex;
					}
					
				}
				
				
				
				if (posIndex >= str.length()-1)
				{
					hitRight = true;
				}
				else
				{
					if (str[posIndex] == ' ' || str[posIndex] == '\n')
					{
						return posIndex;
					}
					
				}
				
				negIndex--;
				posIndex++;
			}
			
			return -1;
			
		};
		
		std::size_t last = 0;
		for (std::size_t i = 1; i < str.length()-1; ++i)
		{
			if (str[i] == '\n')
			{
				last = i;
					splits.push_back(i);
			}
			else if (i - last > divider)
			{
				auto close = findClosest(i, last);
				if (close > 0 && close < str.length()-1)
				{
					last = close;
					splits.push_back(close);
					if (last > i)
					{
						i = last;
					}
				}
				else
				{
					break;
					//throw std::exception();
				}
			}
			
		}
		
		
		return splits;
		throw NotImp();
	}
	
	void SDLLabelViewComponent::storeLastString(const std::string str)
	{
		if (lastString == NULL)
		{
			lastString = new std::string(str);
		}
		else
		{
			*lastString = str;
		}
	}
	
	const std::string& SDLLabelViewComponent::getLastString() const
	{
		if (lastString == NULL)
		{
			lastString = new std::string();
		}
		return *lastString;
	}
	
	void SDLLabelViewComponent::updateTextures()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		//std::cerr << __func__ << "\n\n";
		std::string text = QUtils::String(this->text()).replace("\r\n", "\n");
		unsigned long newSum = Internal::calcCheckSum(text);
		
		if (newSum == lastStringCheckSum)
		{
			//std::cerr << "CheckSum same\n" << std::flush;
			return;
		}
		
		auto& lastStr = getLastString();
		typename std::vector<Segment*>::iterator* changed = NULL;
		auto len = text.length();
		unsigned long sum = 0;
		unsigned long tmpSum;
		
		for (auto it = segments.begin(); it != segments.end(); ++it)
		{
			if ((*it)->end >= len)
			{
				changed = new typename std::vector<Segment*>::iterator(it);
				break;
			}
			
			if ((tmpSum = Internal::calcCheckSum(text, (*it)->start, (*it)->end)) != (*it)->lastCheckSum)
			{
				changed = new typename std::vector<Segment*>::iterator(it);
				break;
			}
			sum += tmpSum;
		}
		
		unsigned long start = 0;
		if (changed == NULL)
		{
			if (segments.size() > 0)
			{
				auto back = segments.back();
				start = back->start;
				delete back;
				segments.pop_back();
			}
		}
		else
		{
			start = (**changed)->start;
			for (auto it = *changed; it != segments.end(); ++it)
			{
				delete *it;
			}
			segments.erase(*changed, segments.end());
			delete changed;
			changed = NULL;
		}
		
		if (text == "")
		{
			return;
		}
		
		std::list<Segment*> newSegments;
		{
			auto splits = splitString(text.substr(start));
			unsigned int splitStart = 0;
			//std::cerr << splits.size() << " splits\n";
			
			for (auto split : splits)
			{
				auto segment = new Segment();
				segment->start = splitStart + start;
				segment->end = split + start;
				if (!(split + start > splitStart + start))
				{
					std::cerr << "NOT TRUE\n";
					throw std::exception();
					
				}
				newSegments.push_back(segment);
				splitStart = split;
			}
			
			
			if (splitStart+start < len - 1)
			{
			auto segment = new Segment();
			segment->start = splitStart + start;
			segment->end = len - 1;
			newSegments.push_back(segment);
			}
			//std::cerr << newSegments.size() << " new segments\n";
			
			
		}
		
		for (auto segment : newSegments)
		{
			segment->lastCheckSum = Internal::calcCheckSum(text, segment->start, segment->end);
		}
		
		//Make surfaces
		{
			auto wrapW = wrapWidth();
			int index = 1;
			auto count = newSegments.size();
			for (auto segment : newSegments)
			{
				//std::cerr << "Creating surface " << index++ << "\t/ " << count << std::endl;
				//std::cerr << "[" << segment->start << ", " << segment->end << "]\n";
				//std::cerr << "\"" << text.substr(segment->start, segment->end-segment->start) << "\"\n";
				segment->surface = _font->surfaceBlendedWrapped(text.substr(segment->start, segment->end-segment->start), (Drawing::SDL::Color)color(), wrapW);
			}
		}
		
		for (auto segment : newSegments)
		{
			segments.push_back(segment);
		}
		
		this->lastStringCheckSum = newSum;
		storeLastString(text);
		//std::cerr << "Textures Updated.\n";
	}
	
	void SDLLabelViewComponent::resetSegments()
	{
		for (auto segment : segments)
		{
			delete segment;
		}
		segments.clear();
		lastStringCheckSum = 0;
		storeLastString("");
	}
	
	bool SDLLabelViewComponent::changed() const
	{
		return TextViewComponent::changed() || _textChanged;
	}
	
}