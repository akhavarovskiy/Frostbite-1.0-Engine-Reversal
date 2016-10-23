#ifndef __FB_ANIMATEDSKELETON_H__
#define __FB_ANIMATEDSKELETON_H__

#include "common.h"
#include "AnimatedModel.h"
#include "AnimationSkeleton.h"

namespace fb
{
	class AnimatedSkeleton : public fb::ByteArray< 0x10 >
	{
	public:
		fb::LinearTransform  m_lastPoseOffset; //0x10
		class AnimationSkeleton* m_animationSkeleton; //0x50
		class AnimatedModel* m_animatedModel; //0x54
	};
} 
#endif