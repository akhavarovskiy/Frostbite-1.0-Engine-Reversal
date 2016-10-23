#ifndef __FB_IPHYSICS_RAYCASTER_H__
#define __FB_IPHYSICS_RAYCASTER_H__

#include "common.h"
#include "physics\RayCastHit.h"

namespace fb
{
	namespace physics
	{
		interface IPhysicsRayCaster
		{
		public:
			virtual bool physicsRayQuery(char * szText, fb::Vec3* RayStart, fb::Vec3* RayEnd, fb::physics::RayCastHit* pTraceRet, int = 0, int = 0);
		};
	}
}

#endif /* _IPHYSICS_RAY_CASTER_H_ */