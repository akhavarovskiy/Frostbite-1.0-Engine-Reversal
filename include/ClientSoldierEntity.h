#ifndef __FB_CLIENTSOLDIERENTITY_H__
#define __FB_CLIENTSOLDIERENTITY_H__

#include <memory>

#include "EASTL\scoped_ptr.h"
#include "EASTL\shared_ptr.h"

#include "Common.h"
#include "AnimatedSoldier.h"
#include "ClientSoldierWeapon.h"
#include "ClientControllableEntity.h"

namespace fb
{
	class ClientSoldierEntity : public ClientControllableEntity, ByteArray < 0xE4 >
	{
	public:
		struct PersonView
		{
			class AnimatedSoldier         * m_animSoldier; 
			class AnimSoundCallbackHandler* m_animSoundHandler; 
			eastl::vector< class MeshModel *>  meshModels; 
		};

		enum HiddenBoneType	
		{
			HideAlways = 0x0,
			HideInVehicleEntries = 0x1,
			HideUsingWeaponMesh = 0x2
		};

		struct HiddenBone
		{
			class SkinnedMeshAsset* m_mesh; 
			unsigned int m_boneIndex; 
			ClientSoldierEntity::HiddenBoneType  m_hideType; 
		};

		class WeaponSwayCallbackImpl : ByteArray < 0x4 > /* SoldierAttributesCallback */
		{
		public:
			fb::ClientSoldierEntity& m_soldierEntity; 
			float m_yawInputLevel; 
			float m_pitchInputLevel; 
			float m_strafeInputLevel; 
			float m_throttleInputLevel; 
			unsigned int m_seed; 
		};

		class SprintInputHandler
		{
		public:
			enum State	
			{
				WaitForward = 0x0,
				WaitReleaseForward = 0x1,
				DoubleTapSprint = 0x2,
				ButtonSprint = 0x3,
				PostSprint = 0x4
			};

			bool m_sprintWasDown; 
			bool m_forwardWasDown; 
			ClientSoldierEntity::SprintInputHandler::State  m_currentState; 
			float m_doubleTapTimer; 
			float m_sprintReleaseTimer; 
		};

		struct State
		{
			/*WeaponSwitchingState*/ 
			int m_currentWeaponId; 
			int m_previousWeaponId; 
			int m_lastPrimary; 
			float m_dpadCooldownTimer; 
		};

		fb::SmartRef< void > vtable_holder;	
		
		unsigned char _pad[8];

		class CorrectionCallbackHandler* m_correctionCallbackHandler; 
		class ClientPlayer* m_player; 
		fb::WeakPtr<class ClientPlayer>  m_previousPlayer; 
		fb::WeakPtr<class ClientVehicleEntity>  m_shotInThisVehicle; 
		fb::WeakPtr<class ClientSoldierEntity>  m_snapAimToSoldier; 
		class ClientSoldierPrediction* m_predictedController; 
		class ClientSoldierReplication* m_replicatedController; 
		class PhysicsEntityBase* m_currentPhysicsEntity; 
		class CharacterPoseConstraints* m_constraints; 
		float m_clearMovementTimer; 
		float m_clearMovementTimer1; 
		class WeaponSwitching* m_predictedWeaponSwitching; 
		class WeaponSwitching* m_predictedWeaponSwitching1;
		class SoldierAimingEnvironment* m_aimingEnvironment;
		class AimingConstraints* m_swimAimingConstraints; 
		class AimingConstraints* m_externalAimingConstraints;
		fb::SmartPtr< class AimingConstraints >  m_parachuteAimingConstraints; 
		eastl::vector< class ClientSoldierWeapon* >  m_weapons; 
		class ClientSoldierWeapon* m_currentAnimatedWeapon; 
		class ClientSoldierWeapon* m_currentSoldierWeaponUsedByRenderer; 
		int m_currentAnimatedWeaponIndex; 
		int m_currentAnimatedWeaponState; 
		float m_timeSinceWeaponFire; 
		float m_timeSinceWeaponHandling; 
		float m_weaponDispersion; 
		float m_weaponUndeployTimer; 
		bool m_weaponDeployRequested; 
		unsigned char m_weaponDeployFlags; 
		float m_deathTimer; 
		float m_cutsceneEndExtrapolationTimeDuration; 
		fb::LinearTransform  m_cameraLocalSpace; 
		fb::LinearTransform  m_deathCameraLocalSpace;
		fb::LinearTransform  m_deathLandingTransform; 
		eastl::vector< class TargetCamera *>  m_cameras; 
		fb::Vec3  m_lastDamageGiverPosition; 
		fb::Vec3  m_lastBulletHitPosition; 
		fb::Vec3  m_lastBulletHitDirection; 
		unsigned int m_lastBoneHitIndex; 
		int m_unknownnegativeone;
		class Material* m_footMaterial; 
		class Material* m_headMaterial; 
		enum EntryInputActionEnum  m_sprintInterruptAction;
		float m_sprintRecoveryTimer; 
		ClientSoldierEntity::PersonView m_localPersonView; //0x3A8 - only present in local client, else equal to NULL  
		ClientSoldierEntity::PersonView m_playerPersonView;//0x3C0 	
		fb::SmartPtr< class GroundHeightCalculator > m_groundHeight;		
		fb::SmartPtr< class GroundHeightCalculator > m_vehicleGroundHeight;
		eastl::vector< fb::ClientSoldierEntity::HiddenBone >  m_hiddenBones; 
		unsigned char m_cameraBone; 
		unsigned char m_cameraFovBone;
		float m_authorativeYaw; 
		float m_authorativePitch;
		bool m_aimingEnabled; 
		class SoldierSound* m_soldierSound; 
		float m_lastHealthChange; 
		unsigned int m_damageGiverPlayerId; 
		unsigned int m_meshShaderSetNumber;
		bool m_primaryWeaponVeteran;
		unsigned char _pad1[ 0xC ];
		fb::LinearTransform  m_meshTransform; 
		unsigned int m_lastZoomLevel;
		//int m_readinessRestriction; 0x4
		//int m_readiness; 
		float m_deadFallingStartPos; 
		float m_deadFallingLerpLength;
		bool m_playingCutscene : 1; 
		bool m_playingLocalAnim : 1; 
		bool m_visible : 1; 
		bool m_isDead : 1; 
		bool m_deadFalling : 1; 
		bool m_deadInWater : 1; 
		bool m_hasFinalRestingPlace : 1; 
		bool m_isShielded : 1; 
		bool m_isFirstPerson : 1; 
		bool m_physicsEnabled : 1; 
		bool m_collisionEnabled : 1; 
		bool m_animHadVisualUpdate : 1; 
		bool m_useCameraBobbing : 1; 
		bool m_weaponMeshWasEnabled : 1; 
		bool m_parachuteMeshEnabled : 1; 
		bool m_shouldSprint : 1; 
		bool m_sprintButtonWasDown : 1;
		bool m_wasSprinting : 1; 
		bool m_hadAnimationUpdate : 1; 
		bool m_derivedStatesUpdated : 1;
		bool m_visualTransformUpdated : 1; 
		unsigned char _pad4[ 0x4 ];
		float m_parachuteYaw;
		bool m_disableParachuteInProgress; 
		class MeshModel* m_parachuteMesh; 
		fb::LinearTransform  m_parachuteMeshTransform; 
		fb::LinearTransform  m_parachuteBaseTiltTransform; 
		fb::LinearTransform  m_parachuteTiltTransform; 
		float m_parachuteRandomXPhase; 
		float m_parachuteRandomZPhase;
		class AnimatedSkeleton* m_parachuteAnimatedSkeleton; 
		class ParachuteAnimationCallbackHandler* m_parachuteAnimationCallbackHandler;
		class BoolParameter* m_parachuteStateParam;
		float m_lastAnimFrameTime;
		fb::Vec3 m_lastAnimFramePos; 
		float m_orderStatusTime; 
		float m_targetTime; 
		unsigned char _pad2[ 0x8 ];
		eastl::vector< class BoneFakePhysics* >  m_fakePhysics; 
		std::auto_ptr< class ClientSoldierEntity::WeaponSwayCallbackImpl >  m_weaponSwayCallback; 
		float m_rumbleUpdateTimer; 
		float m_nextRumbleUpdateTime; 
		float m_maxHealth; 
		eastl::shared_ptr< class ProximityHookImpl >  m_proximityHook; 
		eastl::scoped_ptr< class ShaderParameterCollection >  m_parameterCollection; 	
		bool m_needsWeapon1PResources;
		class OrientationCallback* m_orientationCallback;
		fb::SmartPtr< ClientSoldierEntity::SprintInputHandler >  m_sprintInputHandler; 
		bool m_needMoreAmmo; 
		class FakeAnimatedSoldierCollision* m_fakeAnimatedSoldierCollision; 
		bool m_useFakeAnimatedCollision; 
		ClientSoldierEntity::State  m_correctionState; 
		ClientSoldierEntity::State  m_predictionState; 
		ClientSoldierEntity::State* m_currentState; 

		__forceinline float getHealth( )
		{
			return *( float* ) ( ( unsigned long )this + 0x34 ); 
		}

		__forceinline float getMaxHealth()
		{
			return this->m_maxHealth;
		}
		
		__forceinline int getBoneCount( )
		{
			if( m_playerPersonView.m_animSoldier )
			{
				if( m_playerPersonView.m_animSoldier->m_animationSkeleton )
				{
					if ( !m_playerPersonView.m_animSoldier->m_animationSkeleton->m_boneNames.empty() )
					{
						return m_playerPersonView.m_animSoldier->m_animationSkeleton->m_boneCount;
					}
				}
			}
			return 0;
		}

		__forceinline std::string getBoneName( int m_boneId )
		{
			static std::string ret = std::string();

			if( m_playerPersonView.m_animSoldier )
			{
				if( m_playerPersonView.m_animSoldier->m_animationSkeleton )
				{
					if ( !m_playerPersonView.m_animSoldier->m_animationSkeleton->m_boneNames.empty() )
					{
						return ret = ( char* )m_playerPersonView.m_animSoldier->m_animationSkeleton->m_boneNames.at( m_boneId );
					}
				}
			}
			return ret = "none";
		}

		bool getBoneOrigin( fb::Vec3 * m_boneVec, int m_boneId )
		{
			if( !m_localPersonView.m_animSoldier )
				 return false;
			if( !m_localPersonView.m_animSoldier->m_animatedModel )
				 return false;				
			if( !m_localPersonView.m_animSoldier->m_animatedModel->m_grannyWorldPose )
				 return false;

			m_boneVec->x = m_playerPersonView.m_animSoldier->m_animatedModel->m_grannyWorldPose->at( m_boneId )->trans.x;
			m_boneVec->x = m_playerPersonView.m_animSoldier->m_animatedModel->m_grannyWorldPose->at( m_boneId )->trans.y;
			m_boneVec->x = m_playerPersonView.m_animSoldier->m_animatedModel->m_grannyWorldPose->at( m_boneId )->trans.z;

			return true;
		}
	};
}
#endif