#ifndef __FB_DX11RENDERER_H__
#define __FB_DX11RENDERER_H__

#include "EASTL\vector.h"

#include "IRenderer.h"
#include "RefCountImpl.h"

#include "ViewPort.h"
#include "MsaaModeDescriptor.h"
#include "VideoModeDescriptor.h"

#ifndef VA_DXRENDERER11
#define VA_DXRENDERER11 NULL
#pragma warning ( "[ Warning ] fb::Dx11Renderer : has no predefined offset." )
#endif

namespace fb
{
	enum GpuModel
	{
		GpuModel_Unknown = 0x0,
		GpuModel_Nvidia = 0x1,
		GpuModel_ATI = 0x2
	};

	enum Dx11FeatureLevel
	{
		Dx11FeatureLevel_10_0 = 0x0,
		Dx11FeatureLevel_10_0_Plus = 0x1,
		Dx11FeatureLevel_10_1 = 0x2,
		Dx11FeatureLevel_11_0 = 0x3
	};

	class Dx11Renderer : public RefCountImpl< IRenderer >
	{
		typedef Dx11Renderer this_type;
	public:
		__forceinline static this_type * Instance(void) {
			return *(this_type**) (VA_DXRENDERER11);
		}
		unsigned int m_virtualWidth;						 // this + 0x8 
		unsigned int m_virtualHeight;						 // this + 0xC 
		unsigned int m_virtualHeightBaseOffset; 			 // this + 0x10 
		unsigned int m_virtualWidthBaseOffset; 				 // this + 0x14 
		unsigned int m_renderTargetWidth;      				 // this + 0x18 
		unsigned int m_renderTargetHeight;      			 // this + 0x1C
		eastl::vector< VideoModeDescriptor > m_modeDesc;     // this + 0x20
		eastl::vector< MsaaModeDescriptor  > m_msaaModeDesc; // this + 0x30
		class Dx11DisplaySettings * m_displaySettings;       // this + 0x40 
		class Dx11DisplaySettings * m_oldDisplaySettings;    // this + 0x44 
	    class Dx11DisplaySettingsConsole * m_console;        // this + 0x48
		unsigned char _pad0[4];							     // this + 0x4C
		class Thread* m_ownerThread;						 // this + 0x50
		unsigned int m_threadOwnershipRefCount;				 // this + 0x54
		/*CriticalSection*/ 
		char m_threadOwnershipCriticalSection[24];			 // this + 0x58
		interface IDXGIAdapter* m_adapter;				     // this + 0x70
		interface IDXGIOutput* m_output;					 // this + 0x74 
		interface IDXGIFactory* m_dxgiFactory;				 // this + 0x78	
		interface ID3D11Device* m_device;					 // this + 0x7C
		interface ID3D11DeviceContext* m_context;			 // this + 0x80 
		interface ID3D11InfoQueue* m_infoQueue;				 // this + 0x84
		interface IDXGISwapChain* m_swapChain;				 // this + 0x88
		interface ID3D11RenderTargetView* m_renderTargetView;// this + 0x8C 
		interface ID3D11DepthStencilView* m_depthStencilView;// this + 0x90 
		class Dx11Texture*  m_depthTexture;					 // this + 0x94 
		class ITexture* m_texture[12];						 // this + 0x98
		class ITexture* m_depthStencilTexture2d;			 // this + 0xC8
		DXGI_MODE_DESC  m_outputMode;						 // this + 0xCC
		class Dx11RenderTargetSet* m_activeRenderTargetSet;  // this + 0xE8 
		bool m_useMenuViewport;								 // this + 0xEC 
		Viewport m_menuViewport;							 // this + 0xF0
		Viewport m_viewport;								 // this + 0x108
		Dx11FeatureLevel  m_featureLevel;					 // this + 0x130
		/*dice::ScissorRect*/
		unsigned char _pad1[28];							 // this + 0x134
		class Dx11StateRenderer*  m_stateRenderer;			 // this + 0x150
		float m_forcedAspect;								 // this + 0x154 
		float m_aspect;										 // this + 0x158 
		D3D_DRIVER_TYPE  m_driverType;						 // this + 0x15C 
		HWND__* m_hWnd;										 // this + 0x160 
		unsigned long m_windowedModeStyle;					 // this + 0x164 
		unsigned long m_syncInterval;						 // this + 0x168 
		unsigned int m_gpuCount;							 // this + 0x16C 
		unsigned char m_nvIsStereoEnabled;					 // this + 0x170 
		float m_nvOldStereoSeparation;						 // this + 0x174
		void* m_nvStereoHandle;								 // this + 0x178
		GpuModel  m_gpuModel;								 // this + 0x17C
		bool m_scissorRectEnable;							 // this + 0x180
		bool m_stateRendererActive;							 // this + 0x181
		bool m_supportComputeShaders;						 // this + 0x182
		bool m_dirtySwapChain;								 // this + 0x183 
		bool m_fullScreenActive;							 // this + 0x184
		bool m_occluded;									 // this + 0x185 
		bool m_displaySettingsModeDirty;					 // this + 0x186
		/*EA::Jobs::JobAffinity*/
		unsigned int m_renderJobAffinity;					 // this + 0x188 
		/*ID3D11ShaderResourceView*;*/ 
		unsigned char m_shaders[0x200]; 					 // this + 0x18C 
		interface ID3D11Query * m_query[ 8 ];				 // this + 0x38C
		unsigned int m_frameCounter;						 // this + 0x3AC 
	};
}
#endif