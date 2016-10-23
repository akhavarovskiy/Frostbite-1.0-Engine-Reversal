#ifndef __FB_IRENDERER_H__
#define __FB_IRENDERER_H__

#include "Common.h"	
#include "IRenderTargetSet.h"
	
namespace fb
{
	enum RendererType
	{
		EN_UNK = 0
	};

	interface IRenderer 
	{
	public:
		virtual void AddRef();
		virtual void Release();
		virtual void dtor();
		virtual RendererType getType(); // always returns 1	
		virtual bool beginFrame();	
		virtual void endFrame(bool presentEnable);
		virtual void acquireThreadOwnership();	// ----------------------
		virtual void releaseThreadOwnership();	//  Not used, Nullstubs()
		virtual void verifyThreadOwnership ();	// ----------------------
		virtual int clear(unsigned int mask, struct fb::Vec4 color);
		virtual unsigned int getScreenWidth();	
		virtual unsigned int getScreenHeight();	
		virtual unsigned int getViewportHeightDisplacement();	
		virtual unsigned int getViewportWidthDisplacement();	
		virtual void setScreenWidth ( int width );	
		virtual void setScreenHeight( int height );
		virtual void setVSyncEnable ( bool vsync );	// Null stub
		virtual bool getVSyncEnable ();	
		virtual bool isRenderingLocked();
		virtual bool isHalfPixelOffsetEnabled();	
		virtual bool isTextureFilteringSupported();	
		virtual class ITexture* getColorTexture();	
		virtual class IVertexBuffer* 	    createVertexBuffer	 (class Dx9VertexBufferCreateDesc&   desc);
		virtual class IIndexBuffer*  	    createIndexBuffer 	 (class Dx9IndexBufferCreateDesc&    desc);
		virtual class ITexture*      	    createTexture     	 (class Dx9ITextureBufferCreateDesc& desc);	
		virtual interface IRenderTargetSet* createRenderTargetSet(class Dx9IRenderTargetSetBufferCreateDesc& desc);	

		virtual void setDefaultRenderTarget();
		virtual void setRenderTargetSet(IRenderTargetSet* set);
		virtual IRenderTargetSet* getRenderTargetSet();
	};
}
#endif