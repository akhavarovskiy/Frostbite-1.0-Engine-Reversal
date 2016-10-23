#ifndef __FB_ENTITYMANAGER_H__
#define __FB_ENTITYMANAGER_H__

#include "Common.h"
#include "EASTL\fixed_vector.h"


#include "physics\IPhysicsRayCaster.h"

namespace fb
{
	class EntityManager : public physics::IPhysicsRayCaster
	{
	public:
		fb::SmartPtr< void > vtable_holder;
		unsigned char _pad[ 0x305C ];
		eastl::fixed_vector< eastl::vector< class Entity* >, 1500 > m_entities;
	}; 
}

#endif /* _ENTITY_MANAGER_H_ */