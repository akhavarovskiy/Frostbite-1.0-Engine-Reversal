#ifndef __FB_ANIMATIONSKELETON_H__
#define __FB_ANIMATIONSKELETON_H__

#include "EASTL\vector.h"

namespace fb
{
	class AnimationSkeleton
	{
	public:
		class SkeletonAsset& m_skeletonAsset; 
		/*dice::ResourceProxy<dice::GrannyModel,0,0>*/
		char m_model[0x8]; 
		struct granny_skeleton* m_grannySkeleton; 
		unsigned int m_boneCount; 
		class Hierarchy* m_hierarchy;
		eastl::vector<char const *>  m_boneNames; 
		class AnimationPose * m_pose; 
	};
}

#endif