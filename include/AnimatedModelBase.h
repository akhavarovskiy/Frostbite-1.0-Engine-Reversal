#ifndef __FB_ANIMATEDMODELBASE_H__
#define __FB_ANIMATEDMODELBASE_H__

#include "common.h"
#include "EASTL\fixed_vector.h"

struct granny_world_pose
{
	unsigned __int32 m_AnimatedBoneCount;
	
	eastl::fixed_vector< fb::LinearTransform, 150 > m_bones;

	__forceinline fb::LinearTransform * at( int m_bone )
	{
		return &this->m_bones.mpBegin[ m_bone ];
	}
};

namespace fb
{
	class AnimatedModelBase
	{
	public:
		unsigned char m_durator[0x10]; 
		struct granny_skeleton* m_grannySkeleton; 
		struct granny_local_pose* m_grannyLocalPose; 
		struct granny_world_pose* m_grannyWorldPose;
		unsigned int m_animatedBoneCount;
		float m_distanceFromViewer; 
		bool m_isDirtyLocalPose; 
		bool m_isDirtyWorldPose; 
	};
}

#endif