#ifndef __FB_DX9RENDERER_H__
#define __FB_DX9RENDERER_H__

#include "IRenderer.h"	
#include "RefCountImpl.h"
#include "Dx9RenderTargetSet.h"

#include "EASTL\vector.h"

#ifndef VA_DXRENDERER9
#define VA_DXRENDERER9 NULL
#pragma warning ( "[ Warning ] Dx9Renderer : has no defined offset." )
#endif 

namespace fb
{
	class Dx9Renderer : public RefCountImpl< IRenderer >
	{
	public:
		__forceinline static Dx9Renderer * Instance() {
			return *(Dx9Renderer**) (VA_DXRENDERER9);
		}
		bool m_minimized;
		bool m_maximized;
		unsigned int m_renderTargetWidth;
		unsigned int m_renderTargetHeight;
		unsigned int m_virtualWidth;
		unsigned int m_virtualHeight;
		unsigned int m_virtualHeightBaseOffset;
		unsigned int m_virtualWidthBaseOffset;
		class Thread* m_ownerThread;
		unsigned int m_threadOwnershipRefCount;
		/*dice::CriticalSection*/
		char m_threadOwnershipCriticalSection[0x24];
		unsigned int m_selectedAdapter;
		interface IDirect3D9* m_d3d9;
		interface IDirect3DDevice9* m_device;
		interface IDirect3DSwapChain9* m_swapChain;
		class Dx9RenderTargetSet * m_activeRenderTargetSet;
		interface IDirect3DSurface9* m_defaultRenderTarget;
		interface IDirect3DSurface9* m_defaultDepthTarget;
		class Dx9StateCache* m_stateCache;
		class Dx9DisplaySettings* m_displaySettings;
		class Dx9DisplaySettings* m_oldDisplaySettings;
		class Dx9StateRenderer*   m_stateRenderer;
		class ITexture*			  m_textures[12];
		class ITexture*			  m_depthStencilTexture2d;
		bool m_useMenuViewport;
		unsigned char _pad[0xC];
		Viewport m_menuViewport;
		Viewport m_viewport;
		float m_forcedAspect; 
		int m_scissorRectEnable;
		ScissorRect m_scissorRect[3]; 
		bool m_stateRendererActive; 
		bool m_dirtySwapChain; 
		float m_desktop_aspect; 
		float m_aspect; 
		eastl::vector< class Dx9DeviceResetListener *>  m_deviceResetListeners;
		unsigned int m_maxAnisotropy;
		bool m_supportsR2VB; 
		bool m_supportsFetch4; 
		bool m_supportsVertexTextures; 
		bool m_supportsPcf; 
		bool m_supportsHdrFiltering; 
		bool m_supportsDialogBoxMode; 
		int m_gpuModel; 
		unsigned int m_gpuCount; 
		unsigned char m_nvIsStereoEnabled; 
		float m_nvOldStereoSeparation; 
		void* m_nvStereoHandle; 
		bool m_deviceIsLost;
		bool m_isWinXP; 
		class Dx9TempResourceAllocator* m_tempResourceAllocator; 
		char  m_vbTempMap[0x1C]; 
		char  m_ibTempMap[0x1C]; 
		char _pad1[0x24];
		HWND__* m_hWnd;
		D3DDEVTYPE  m_deviceType;
		bool m_fullScreenActive; 
		bool m_displaySettingsModeDirty; 
		long m_windowedModeStyle; 
		long m_fullScreenModeStyle;
		int m_renderJobAffinity;
	};
}
#endif

