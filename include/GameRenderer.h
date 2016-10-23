#ifndef __FB_GAMERENDERER_H__
#define __FB_GAMERENDERER_H__

#include "RenderView.h"
#include "IGameRenderer.h"
#include "GameRenderSettings.h"

#ifndef VA_GAME_RENDERER
#define VA_GAME_RENDERER NULL

#pragma message ("[ Warning ] GameRenderer : has no defined offset.")  

#endif

namespace fb
{
   class GameRenderer : public IGameRenderer
   {
   public:
	   __forceinline static GameRenderer * Instance( void ) {
			return *(GameRenderer**)(VA_GAME_RENDERER);
	   }
	    /* Called from vtable */
	   __forceinline fb::Vec2 getResolution()
	   {
		   return ( (fb::Vec2(__stdcall*)()) *(DWORD*)((DWORD)vtable_holder.m_ptr + 0x30) )( );
	   }
	  
	   fb::SmartPtr< void > vtable_holder;
	   fb::SmartRef< class GameRenderSettings >  m_settings;
	   class RenderView m_view;
	   struct IGameRenderer::ViewParams  m_viewParams;
   };
}
#endif /* _GAME_RENDER_H_ */