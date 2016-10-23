#ifndef __FB_CLIENTGAMEENTITYMANAGER_H__
#define __FB_CLIENTGAMEENTITYMANAGER_H__

#include "common.h"
#include "GameEntityManager.h"

namespace fb
{
	class ClientGameEntityManager : public GameEntityManager
	{
	public:
		fb::SmartRef< void > vtable_holder;
	};
}

#endif /* _CLIENT_GAME_ENTITY_MANAGER_H_ */