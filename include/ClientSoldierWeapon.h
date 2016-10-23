#ifndef __FB_CLIENTSOLDIERWEAPON_H__
#define __FB_CLIENTSOLDIERWEAPON_H__

#include "SoldierWeaponData.h"

namespace fb
{
	class ClientSoldierWeapon
	{
		class WeaponState
		{
		public:
			class AnimatedSoldierWeapon* m_animation;
			eastl::vector< class BoneFakePhysics * >  m_fakePhysics;
			eastl::vector< /*class Mesh*/ void* >  m_meshes;
			/*dice::ResourceProxy<dice::MeshSet const ,0,0>*/ char  m_meshZoom[0x8];
			unsigned short m_meshInstanceHandle;
			unsigned short m_meshZoomInstanceHandle;
			eastl::vector< unsigned int >  m_hiddenBones;
		};
	public:
		fb::SmartPtr< void > vtable_holder;

		class SoldierWeaponData * m_data; 
		eastl::vector< ClientSoldierWeapon::WeaponState >  m_weaponStates1p; 
		eastl::vector< ClientSoldierWeapon::WeaponState >  m_weaponStates3p; 
		class WeaponLagEffect* m_cameraLagEffect; 
		class ClientSoldierAimingSimulation* m_authorativeAiming;
		class ClientAimingReplication* m_replicatedAiming;
		class ClientLockingController* m_lockingController; 
		class ClientWeaponFiringEffects* m_firingEffects; 
		class WeaponFiring* m_predictedFiring; 
		class WeaponFiring* m_correctedFiring; 
		class ClientWeaponFiringReplication* m_replicatedFiring; 
		class /*ClientSoldierWeapon::*/CorrectionCallbackHandler* m_correctionCallbackHandler; 
		class AnimatedSoldier* m_animatedSoldier1p; 
		class AnimatedSoldier* m_animatedSoldier3p; 
		unsigned short m_weaponInstanceId; 
		unsigned int m_projectileBoneIndex; 
		class WeaponFirstPersonAsyncLoadedResourceSet* m_1pAsyncLoadedResourceSet; 
		bool m_1pMeshesCreated; 
		bool m_1pMeshesDestroyed; 
		bool m_meshesUsed; 
	};

}

#endif