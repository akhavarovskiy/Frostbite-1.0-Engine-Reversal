#ifndef __FB_FRUSTRUM_H__
#define __FB_FRUSTRUM_H__

/* vec3.h */
#include "common\vec3.h"
/* Plane.h */
#include "common\Plane.h"
/* AxisAlignedBox.h */
#include "common\AxisAlignedBox.h"
/* Lineartransform.h */
#include "common\Lineartransform.h"

namespace fb
{
	struct Frustum
	{
	  LinearTransform m_transform;
	  AxisAlignedBox m_boundingBox;
	  Vec3 m_corners[8];
	  Vec3 m_center;
	  Plane m_planes[6];
	  unsigned int m_planeSignBits[6];
	  float m_radius;
	  float m_radiusSqr;
	  bool m_rightHanded;
	};
}

#endif /* __FB_FRUSTRUM_H__ */