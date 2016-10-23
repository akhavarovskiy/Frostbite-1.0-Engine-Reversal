#ifndef __FB_LINEARTRANSFORM_H__
#define __FB_LINEARTRANSFORM_H__

#include "common\vec3.h"

namespace fb
{
	struct LinearTransform
	{	
		/*
		
		LinearTransform(void) {
			left = Vec3(0, 0, 0);
			up = Vec3(0, 0, 0);
			forward = Vec3(0, 0, 0);
			trans = Vec3(0, 0, 0);
		}
		

		~LinearTransform(void) {}
	
		LinearTransform(float x)
			left = Vec3(x, 0, 0);
			up = Vec3(0, x, 0);
			forward = Vec3(0, 0, x);
			trans = Vec3(0, 0, 0);
		}

	
		LinearTransform(Vec3& left_, Vec3& up_, Vec3& forward_, Vec3& translation_{
			left = left_;
			up = up_;
			forward = forward_;
			trans = translation_;
		}
	
	
		inline LinearTransform  & operator = (LinearTransform lt){
			this->forward = lt.forward;
			this->left = lt.left;
			this->up = lt.up;
			this->trans = lt.trans;
			return *this;
		}*/

		Vec3 left; 
		Vec3 up; 
		Vec3 forward; 
		Vec3 trans;
	};
}
#endif