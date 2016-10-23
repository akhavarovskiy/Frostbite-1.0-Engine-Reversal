#ifndef __FB_CLIENTCONTROLLABLEENTITY_H__
#define __FB_CLIENTCONTROLLABLEENTITY_H__

#include "common.h"
#include "EASTL\vector.h"

namespace fb
{
	class ClientControllableEntity : public fb::ByteArray < 0x50 > 
	{
	public:
		fb::SmartRef< void > vtable_holder;			
		unsigned char _pad[68];
		float m_spottedTime; 
		bool m_isSpottedFromClient; 
		fb::LinearTransform  m_lastKnownPosition; 
		float m_lastKnownPositionTime; 
		fb::TeamId  m_spotterTeamId; 
		eastl::vector<float>  m_warningTimer; 
		eastl::vector<unsigned int>  m_warningEffectHandle; 
		class EntryCorrectionTask * m_correctionTask; 
		unsigned int m_remoteGhostId; 
		unsigned int m_correctingEntry; 
		unsigned char _pad1[12];
	};	
}
#endif