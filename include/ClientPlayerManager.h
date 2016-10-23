#ifndef __FB_CLIENTPLAYERMANAGER_H__
#define __FB_CLIENTPLAYERMANAGER_H__ 

#include "EASTL\vector.h"

#include "Player.h"
#include "ClientPlayer.h"

namespace fb
{
	class ClientPlayerManager
	{
		typedef eastl::vector< class ClientPlayer *> Players;
		typedef class ClientPlayer** PlayerIterator;
	public:
		virtual void update(float deltaTime);

		char _buf[0x90];

		Players m_clientPlayers;
		Players m_aiClientPlayers; 
		class ClientPlayer * m_localPlayer; 
		PlayerIterator       m_idToPlayerMap; 
		bool m_idToPlayerMapIsDirty; 

		class ClientPlayerManagerPlayer * m_networkablePlayers;
		class ClientNetworkableGroupint * m_networkablePlayerGroups; 
	};
}

#endif