#ifndef __FB_IGAMERENDERER_H__
#define __FB_IGAMERENDERER_H__

#include "Common.h"

namespace fb
{
	interface IGameRenderer
	{
		enum BloodEffectPosition;
		struct ViewParams;
	public:
		fb::SmartPtr< void > vtable_holder;
		bool m_init;
	};

	enum IGameRenderer::BloodEffectPosition
	{
		BepTop = 0x0,
		BepRight = 0x1,
		BepBottom = 0x2,
		BepLeft = 0x3
	};

	struct IGameRenderer::ViewParams
	{
		bool visible;
		float worldFadeAmount;
		float globalFadeAmount;
		float blurAmount;
		float dofFocusDistance;
		class ScopeFilterData * scopeFilterData;
		class HudFxData * hudFxData;
		class BlurFilter * foregroundBlurFilter;
		float foregroundBlurFilterDeviation;
		float shadowmapViewDistance;
		float shadowmapMinFov;
		bool hudPipEnable;
		/*dice::WorldScreenViewport*/ char hudPipViewport[0x10];
		float crosshairDepth;
	};
}
	
#endif /* IGAME_RENDER_H_*/