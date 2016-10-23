#ifndef __FB_CLIENTPLAYER_H__
#define __FB_CLIENTPLAYER_H__

#include <string>

#include "common.h"
#include "EASTL\string.h"

#include "Player.h"
#include "ClientSoldierEntity.h"
#include "ClientControllableEntity.h"

namespace fb
{
	/* ClientPlayer has no predefined vtable */
	class ClientPlayer : public Player , ByteArray < 0xAF0 > /* Padding after Player*/  
	{
	public:	
		class ClientControllableEntity* m_attachedControllable;
		unsigned int m_attachedEntryId;
		class ClientSoldierEntity * m_soldier;	
		unsigned char _pad1[4];	
		class EntryInput* m_input; 
		class EntryInputState* m_inputState; 	
		unsigned char _pad2[16];	
		fb::TeamId  m_lastTeamHit;
		int m_lastKit; 
		int m_inputNetworkId; 	
		unsigned char _pad3[12];	
		eastl::basic_string< char > m_clantag;
		bool m_muted;
		float m_timeSinceGivingDamage; 
		float m_visibleTime; 
		float m_inVisibleTime; 
		float m_lastRespawnTime; 

		__forceinline bool isDead()
		{   /* Null soildier entity = dead player*/
			return (  m_soldier == NULL );
		}
		
		__forceinline fb::ClientSoldierWeapon * getWeapon( )
		{
			fb::ClientSoldierEntity * m_soldier = this->m_soldier;
			
			if( m_soldier )
			{
				if( m_soldier->m_currentAnimatedWeaponIndex >= 0 )
				{
					if( !m_soldier->m_weapons.empty() )
					{
						fb::ClientSoldierWeapon * m_weapon = m_soldier->m_weapons.at( m_soldier->m_currentAnimatedWeaponIndex );
						
						if( m_weapon )
						{
							return  m_weapon;
						}
					}
				}
			}	
			return NULL;
		}
		
		__forceinline std::string weaponName( )
		{
			static std::string ret = std::string();

			fb::ClientSoldierWeapon * m_weapon = getWeapon( ); 

			if( m_weapon )
			{
				if( m_weapon->m_data )
				{
					if( !m_weapon->m_data->m_weaponAssetName.empty() )
					{
						ret = ( char * )( m_weapon->m_data->m_weaponAssetName.c_str() + 2 );  // removing the "h_" prefix

						if( m_soldier->m_primaryWeaponVeteran && m_soldier->m_currentAnimatedWeaponIndex == 0 )
						{
							ret.insert( ret.length() , "(V)" );
						}
						return ret;
					}
				}
			}	
			return ret = "none";
		}
	};
}

#endif /* _CLIENT_PLAYER_H_ */