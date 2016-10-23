#ifndef __FB_MAT4_H__
#define __FB_MAT4_H__

#include <d3dx9.h>
struct _Mat4
{
	union 
	{
		struct
		{
			float  _11, _12, _13, _14;
			float  _21, _22, _23, _24;
			float  _31, _32, _33, _34;
			float  _41, _42, _43, _44;
		};
		float m_data[4][4];
	};
};

namespace fb
{
	struct Mat4 : public _Mat4
	{
		Mat4(void) {}
		~Mat4(void) {}
		
#ifdef __D3DX9MATH_H__
		inline operator D3DXMATRIX(void) {
			return *reinterpret_cast<D3DXMATRIX*> (this->m_data);
		}

		inline operator D3DXMATRIX*(void){
			return reinterpret_cast<D3DXMATRIX*> (this->m_data);
		}
#endif
		__forceinline float dot( int row , Vec3 * v )
		{
			return ((this->m_data[0][row] * v->x) +
			    	(this->m_data[1][row] * v->y) +
				    (this->m_data[2][row] * v->z) + 
					 this->m_data[3][row]       );
		}
	};
}
#endif