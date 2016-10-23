#ifndef __FB_VIDEO_MODE_DESCRIPTOR_H__
#define __FB_VIDEO_MODE_DESCRIPTOR_H__

namespace fb
{
	struct VideoModeDescriptor
	{
		unsigned int Width; 	// this + 0x0 
		unsigned int Height; 	// this + 0x4 
		float RefreshRate; 		// this + 0x8
		int Format; 			// this + 0xC
		int ScanlineOrdering;   // this + 0x10 
		int Scaling;            // this + 0x14 
		unsigned int RefreshRateNumerator;   // this + 0x18
		unsigned int RefreshRateDenominator; // this + 0x1C
	};
}
#endif