#ifndef __FB_RAYCASTHIT_H__
#define __FB_RAYCASTHIT_H__

#include "common.h"

namespace fb
{
	namespace physics
	{
		class RayCastHit
		{
		public:
			fb::Vec3  m_position; 
			fb::Vec3  m_normal; 
			class PhysicsEntityBase* m_rigidBody;
			unsigned int m_part; 
			unsigned int m_bone; 
			float m_lambda; 
			class Material* m_material; 
		};
	}
}
#endif /* _RAY_CAST_HIT_H_ */