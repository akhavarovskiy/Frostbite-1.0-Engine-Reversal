#ifndef __FB_VIEWPORT_H__
#define __FB_VIEWPORT_H__

namespace fb
{
	struct Viewport
	{
		unsigned int x;		// this + 0x0
		unsigned int y;		// this + 0x4
		unsigned int width;	// this + 0x8 
		unsigned int height;// this + 0xC
		float minZ;			// this + 0x10
		float maxZ;			// this + 0x14
		unsigned char _pad1[8];
	};
}
#endif
