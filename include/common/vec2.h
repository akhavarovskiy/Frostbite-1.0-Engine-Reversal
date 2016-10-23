#ifndef __FB_VEC2_H__
#define __FB_VEC2_H__

#pragma warning( push )
#pragma warning( disable : 4172 ) 

/* Vec2 base : sizeof() = 0x8. */
struct _Vec2
{
	union 
	{
		struct 
		{
			float x, y;
		};
		float data[2];
	};
};
	
namespace fb
{
	struct Vec2 : public _Vec2
	{
		Vec2() {}
		
		Vec2( float v ) 
		{
			x = v;
			y = v;
		}
		
		Vec2(float _x , float _y)
		{
			x = _x;
			y = _y;
		}
		~Vec2(){ }
		
		Vec2 operator = ( Vec2 v )
		{
			x = v.x;
			y = v.y;		
			return *this;
		}

	};
}
#pragma warning( pop )
#endif