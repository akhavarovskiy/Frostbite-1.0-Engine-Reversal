#ifndef __FB_CLIENTGAMECONTEXT_H__
#define __FB_CLIENTGAMECONTEXT_H__

#include "EASTL\string.h"
	
#include "ClientPlayerManager.h"
#include "ClientGameEntityManager.h"

#ifndef VA_CLIENT_GAME_CONTEXT
#define VA_CLIENT_GAME_CONTEXT NULL
#pragma message ( "[ Warning ] ClientGameContext : has no defined offset" )
#endif

namespace fb
{
	class ClientGameContext
	{
	public:
		static ClientGameContext * Instance(void) {
		   return ((ClientGameContext*(_cdecl*)(void))VA_CLIENT_GAME_CONTEXT)(); //0x16372C0
		}
		virtual bool SinglePlayer();  /* Ironic considering the fact there are two executables*/
		virtual eastl::basic_string< char > * levelname();
	
		class ClientGameEntityManager	 *m_clientEntityManager;		  
		class ClientPlayerManager  		 *m_clientPlayerManager;	
	};
}

#endif