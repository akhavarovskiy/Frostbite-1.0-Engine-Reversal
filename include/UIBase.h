//UIBase: 0x1C0E0F8
#ifndef __FB_UIBASE_H__
#define __FB_UIBASE_H__

#include "EASTL\list.h"
#include "EASTL\string.h"


#include "Common.h"

//#include "UIRender.h"

#ifndef VA_UI_BASE
#define VA_UI_BASE NULL
#pragma warning( "[ Warning ] UIBase : has no predefined offset." )
#endif

namespace fb
{
	enum UIRenderPriority
	{
		UIRenderPriority_1 = 0x0,
		UIRenderPriority_2 = 0x1,
		UIRenderPriority_Count = 0x2
	};

	class UIBase 
	{
		typedef UIBase this_type;
	public:
		__forceinline static this_type *Singleton(void) {
			return *(this_type**) (VA_UI_BASE);
		}
		virtual void dtor();
		virtual bool init(class VirtualFileSystem* fileSystem);
		virtual void update(float delta);
		virtual void render(float deltaTime);
		virtual void buildDraw(float deltaTime);
		virtual void beginDraw(unsigned int frameIndex);
		virtual void draw(float deltaTime, fb::UIRenderPriority priority, unsigned int frameIndex);
		virtual void endDraw(unsigned int frameIndex);
		virtual void updateScene(float deltaTime, unsigned int frameIndex, bool direct);
		virtual bool isSceneUpdateActive(bool direct);
		virtual void drawScene(float deltaTime, bool direct);
		virtual void onAsyncFinished(eastl::basic_string<char>& assetName);

		bool m_initialised;				  // this + 0x4
		class UILogic*      m_active;     // this + 0x8
		class UIFontSystem* m_fontSystem; // this + 0xC
		unsigned char _pad0[ 0x208CB0 ];  // this + 0x208CBC
		fb::Vec4 m_globalFadeColor;       // this + 0x208CC0
		float m_updateTime; 			  // this + 0x208CD0
		float m_updateDelta; 			  // this + 0x208CD4
		eastl::list <class UIString* > m_strings;    // this + 0x208CD8 Length = 0xC
		bool m_enableTraces;						 // this + 0x208CE4
		eastl::basic_string<char>  m_basePath;       // this + 0x208CE8 Length = 0xC
		eastl::basic_string<char>  m_soundBasePath;  // this + 0x208CFC Length = 0xC
		class VirtualFileSystem* m_fileSystem;		 // this + 0x208D00
		bool m_renderingEnabled;					 // this + 0x208D04
		bool m_debugPause;							 // this + 0x208D05
		unsigned char _pad1[0x78];					 // this + 0x208D08	
		unsigned int m_frameIndex;					 // this + 0x208D80
		unsigned char _pad2[0x18];					 // this + 0x208D08	
		unsigned int  m_activeRenderFrame;			 // this + 0x208D9C 
		fb::Mat4 m_textTransformation;				 // this + 0x208DA0 
		class UIRender* m_render;							// this + 0x208DE0
		class UIRenderPipeline* m_renderPipeline;			// this + 0x208DE4
		class IUIRenderCacheManager* m_renderCacheManager;  // this + 0x208DE8
	};
}

#endif