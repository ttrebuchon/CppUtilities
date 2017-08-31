#include <QUtils/GUI/SDL/TextureView.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/SDL/RenderTarget.h>
#include <QUtils/GUI/SDL/AppWindow.h>
#include <QUtils/GUI/Errors.h>


namespace QUtils::GUI::SDL
{
	SDLTextureView::SDLTextureView(int w, int h) : SDLView(), texture(NULL), tmpRen(NULL), texW(w), texH(h)
	{
		
	}
	
	SDLTextureView::~SDLTextureView()
	{
		if (texture != NULL)
		{
			delete texture;
		}
	}
	
	
	void SDLTextureView::setWindow(AppWindow* win)
	{
		SDLView::setWindow(win);
		auto sdlWin = dynamic_cast<SDLAppWindow*>(win);
		texture = new Drawing::SDL::Texture(sdlWin->getRenderer(), Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, texW, texH);
	}
	
	void SDLTextureView::update()
	{
		if (changed())
		{
			auto sdlWin = dynamic_cast<SDLAppWindow*>(window);
			if (sdlWin == NULL)
			{
				throw IncompatibleGUI_TypeException().Msg("Window isn't an SDLAppWindow").File(__FILE__).Function(__func__);
			}
			tmpRen = sdlWin->getRenderer();
			tmpRen->target(texture);
			tmpRen->setDrawColor(0, 0, 0, 255);
			tmpRen->clear();
			updateTexture();
			tmpRen->renderPresent();
			tmpRen = NULL;
		}
	}
	
	void SDLTextureView::render(RenderTarget* genericTarget, int x, int y, int w, int h)
	{
		auto sdlTarget = dynamic_cast<SDLRenderTarget*>(genericTarget);
		if (sdlTarget == NULL)
		{
			throw IncompatibleGUI_TypeException().Msg("RenderTarget isn't an SDLRenderTarget").File(__FILE__).Function(__func__);
		}
		auto ren = sdlTarget->getRenderer();
		
		
		calcRenderDimensions(w, h);
		
		texture->alphaMod(static_cast<unsigned char>(255*opacity()));
		texture->blendMode(Drawing::SDL::BlendMode::Blend);
		ren->copy(texture, NULL, {x, y, w, h});
	}
	
	Drawing::SDL::Renderer* SDLTextureView::getRenderer()
	{
		return tmpRen;
	}
	
	int SDLTextureView::nativeWidth() const
	{
		return texW;
	}
	
	int SDLTextureView::nativeHeight() const
	{
		return texH;
	}
}