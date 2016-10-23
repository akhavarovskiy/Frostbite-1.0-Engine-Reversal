#ifndef __FB_ANIMATED_SOLDIER_H__
#define __FB_ANIMATED_SOLDIER_H__

#include "AnimatedSkeleton.h"

namespace fb
{
	class AnimatedSoldier : public AnimatedSkeleton 
	{
	public:
		class DelayedLocalAnimation
		{
		public:
			class AnimTreeDataAsset* m_animTree; 
			class AnimationCallbackHandler* m_callbackHandler;
			enum  LocalAnimationType  m_localAnimType; 
			int m_localAnimIndex;
			eastl::basic_string<char>  m_loopParamName;
			eastl::basic_string<char>  m_loopWeightParamName; 
			bool m_waitingToPlay;
		};

		DelayedLocalAnimation * getLocalAnim()
		{
		   return (DelayedLocalAnimation*)( (DWORD)this + 0x198 );
		}	
	};
}
#endif