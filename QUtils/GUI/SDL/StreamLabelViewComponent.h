#pragma once

#include "LabelViewComponent.h"

#include <iostream>
#include <sstream>


namespace QUtils::GUI::SDL
{
	class SDLStreamLabelViewComponent : public SDLLabelViewComponent
	{
		public:
		
		class Buf : public std::basic_stringbuf<char>
		{
			private:
			SDLStreamLabelViewComponent* label;
			
			protected:
			
			virtual std::streambuf* setbuf(char*, std::streamsize) override;
			
			public:
			Buf(SDLStreamLabelViewComponent*);
			
			
			virtual int sync() override;
			virtual std::streamsize xsputn(const char* s, std::streamsize n) override;
			virtual int overflow(int c = EOF) override;
			
			virtual std::string str() const;
			virtual void str(const std::string&);
		};
		
		private:
		
		
		protected:
		std::string _text;
		Buf* _buf;
		
		void setTextChanged();
		void setTextChangedAsync();
		
		public:
		
		
		SDLStreamLabelViewComponent(const std::string id, bool touch, const std::string font, unsigned int fontSize);
		SDLStreamLabelViewComponent(bool touch, const std::string font, unsigned int fontSize);
		SDLStreamLabelViewComponent(const std::string id, const std::string font, unsigned int fontSize);
		SDLStreamLabelViewComponent(std::ostream& stream, const std::string font, unsigned int fontSize);
		virtual ~SDLStreamLabelViewComponent();
		
		virtual std::string text() const override;
		virtual void text(const std::string) override;
		virtual void clear();
		
		const Buf* buf() const;
		Buf* buf();
		
	};
		
		
		
		
}