#ifndef __FB_UI_RENDER_PIPELINE_H__
#define __FB_UI_RENDER_PIPELINE_H__

#include "UIRenderPipelineData.h"

namespace fb
{
	class UIRenderPipeline
	{
		/* Enums */
		enum EnabledTypes;

		/* Classes */
		class Render;
	public:
		unsigned int m_enqueueContextIndex[2];         // this + 0x0 Length = 0x8
		unsigned int m_renderContextIndex[2];		   // this + 0x8 Length = 0x8
		UIRenderPipelineData m_data[2];				   // this + 0x10 Length = 0x160
		UIRenderPipeline::Render* m_render;			   // this + 0x170 Length = 0x4
		UIRenderPipeline::EnabledTypes m_enabledTypes; // this + 0x174 Length = 0x4
	};

	enum UIRenderPipeline::EnabledTypes
	{
		None = 0x0,
		Primitive = 0x1,
		Text = 0x2,
		Icon = 0x4,
		Quad = 0x8,
		Bink = 0x10,
		All = 0x1F
	};

	class UIRenderPipeline::Render
	{
	public:
		virtual void renderPrimitive(class UIRenderCacheManager* cacheManager, UIRenderPipelineData::Primitive* primitive, unsigned int frameIndex, bool isCrosshair);
		virtual void renderText(class UIRenderCacheManager* cacheManager, UIRenderPipelineData::Text* text, unsigned int frameIndex);
		virtual void renderIcon(class UIRenderCacheManager* cacheManager, UIRenderPipelineData::Icon* icon, unsigned int frameIndex);
		virtual void renderQuad(class UIRenderCacheManager* cacheManager, UIRenderPipelineData::Quad* quad, unsigned int frameIndex);
		virtual void renderBink(class UIRenderCacheManager* cacheManager, UIRenderPipelineData::Bink* bink, unsigned int frameIndex);
		virtual void renderTriangleSoup(class UIRenderCacheManager* cacheManager, UIRenderPipelineData::TriangleSoup* triangleSoup, unsigned int frameIndex);
	};
}
#endif