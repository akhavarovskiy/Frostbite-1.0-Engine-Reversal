#ifndef __FB_REFCOUNTIMPL_H__
#define __FB_REFCOUNTIMPL_H__

#include "AutoInit.h"

namespace fb
{
	template< typename T > class RefCountImpl : public T
	{
	public:
		//virtual void AddRef(void);
		//virtual void Release(void);
	private:
		AutoInit<T,0>  m_refCount; // Offset = this + 0x4 Length = 0x4
	};
}
#endif