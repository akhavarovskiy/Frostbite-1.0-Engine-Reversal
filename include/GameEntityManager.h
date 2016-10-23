#ifndef __FB_GAMEENTITYMANAGER_H__
#define __FB_GAMEENTITYMANAGER_H__

#include "common.h"
#include "EntityManager.h"

namespace fb
{
	class GameEntityManager
	{
	public:
		fb::SmartRef< void > vtable_holder;
		EntityManager * m_entityManager;
	};
}

#endif /* _GAME_ENTITY_MANAGER_H_ */