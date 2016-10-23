#ifndef __FB_PLAYER_H__
#define __FB_PLAYER_H__

#include "common.h"
#include "EASTL\string.h"

#include "EntryComponent.h"
//#include "..\fb_moh\SoldierEntity.h"

namespace fb
{
	enum TeamId
	{
		TeamNeutral = 0x0,
		Team1 = 0x1,
		Team2 = 0x2
	};
	
	class Player
	{
	public:
		virtual void dtor();
		virtual class ClientPlayer * clientPlayer();
		virtual class ServerPlayer * serverPlayer();
		virtual class SoldierEntity  * soldier();			
		virtual class EntryComponent * entry  ();			
		virtual class ControllableEntity* controllable();	
		virtual bool isInVehicle();							
		virtual eastl::basic_string<char>& name();
		virtual struct LinearTransform transform();			
		virtual bool isLocal();								
		virtual void setFocusEntity(unsigned int focusTime, class GameEntity* focusEntity);
		
		eastl::basic_string< char > m_name;
		class EntryComponent * m_entry; 
		char m_strname[24];
		fb::TeamId m_teamId;
		fb::TeamId m_teamPreference;	
		unsigned char _pad0[20];
		int  m_voiceChannelf; 
		unsigned short m_voiceSlot;
		float m_timeToRespawn; 
		unsigned int m_lastVehicleCameraIndex; 
		unsigned int m_id; 
		unsigned int m_analogInputEnableMask; 
		double m_digitalInputEnableMask; 	
		bool m_isSquadLeader : 1; 
		bool m_isSquadSpawner : 1; 
		bool m_isSquadSpawnAllowed : 1;
		bool m_isSquadPrivate : 1;

		//char _pad1[2804];
	};
}	
#endif	 /* _PLAYER_H_ */ 