#ifndef __FB_UI_RENDER_H__
#define __FB_UI_RENDER_H__

#include "UIRenderPipeline.h"

namespace fb
{
	class UIRender : public UIRenderPipeline::Render
	{
	public:
		virtual void dtor();
		class UIBase* m_base;
	};
};
#endif