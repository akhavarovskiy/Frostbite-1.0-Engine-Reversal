#ifndef _FB_VEC4_H_
#define _FB_VEC4_H_

/* Vec4 base : sizeof() = 0x16. */
struct _Vec4 
{
	union {
		struct {
			float x, y, z, w;
		};
		float data[4];
	};
};
	

namespace fb
{
	struct Vec4 : public _Vec4
	{
		Vec4() {}
		Vec4( float x, float y, float z, float w ) 
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		~Vec4() {}
	};
}

#endif /* _FB_VEC4_H_ */