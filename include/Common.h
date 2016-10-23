#ifndef __FB_COMMON_H__
#define __FB_COMMON_H__

#pragma warning ( push )
#pragma warning ( disable : 4172 ) 

#include "common\vec2.h"
#include "common\vec3.h"
#include "common\vec4.h"
#include "common\Plane.h"
#include "common\Mat4.h"
#include "common\AxisAlignedBox.h"
#include "common\Lineartransform.h"
#include "common\Frustum.h"
#include "RefCountImpl.h"
#include "ScissorRect.h"
#include "ViewPort.h"

namespace fb
{	  
	template< typename T > struct SmartRef
    {
        T* m_ptr;
    }; 

    template< typename T > struct SmartPtr
    {
        T* m_ptr;
    }; 

	template< typename T > struct WeakPtr
    {
        T* m_ptr;
    };

	/*  cast as a class to allow inheritance padding
		-------------------------------------------- */
	template < size_t size > class ByteArray
	{
	public: 
		template < typename T > T at( size_t at )	
		{
			return *(T*)( this->buf[ at ] );
		}
	private:
		unsigned char buf[ size ];
	};
}
#pragma warning ( pop )
#endif /* _FB_COMMON_H_ */