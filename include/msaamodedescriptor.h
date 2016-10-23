#ifndef __FB_MSAA_MODE_DESCRIPTOR_H__
#define __FB_MSAA_MODE_DESCRIPTOR_H__

#include "EASTL\string.h"

namespace fb
{
	struct MsaaModeDescriptor
	{
		unsigned char SampleCount;				// this + 0x0 
		unsigned char Quality;     			    // this + 0x1 
		eastl::basic_string<char>  Description; // this + 0x4
	};
}

#endif
