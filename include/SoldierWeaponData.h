#ifndef __FB_SOLDIERWEAPONDATA_H__
#define __FB_SOLDIERWEAPONDATA_H__

#include "EASTL\string.h"

namespace fb
{
	class SoldierWeaponData
	{
	public:
		SmartPtr< void > vtable_holder;
		unsigned char _pad[0x8];
		eastl::basic_string< char > m_weaponAssetName;
	};
}
#endif