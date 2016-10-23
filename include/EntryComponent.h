#ifndef __FB_ENTRYCOMPONENT_H__
#define __FB_ENTRYCOMPONENT_H__

namespace fb
{
	class EntryComponent
	{
	public:
		class WeaponInfo
		{
		public:
			virtual void worldTransform();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual void getState();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual void addWeaponFiringCallbacks();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual void removeWeaponFiringCallbacks();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual class WeaponFiring* weaponFiring();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual class WeaponFiringEffects* weaponFiringEffects();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual class WeaponInformation* aiInfo();	//TODO: Pure Function, update params from non-abstract derived class!
			virtual bool isReloading();	//TODO: Pure Function, update params from non-abstract derived class!

		};
	
		class EntrySorter
		{
		public:

		};
		class Subscriber
		{
		public:
			virtual void onUnSpawn();
			virtual void onWeaponAdded(class EntryComponent::WeaponInfo* weapon);
			virtual void onWeaponRemoved(class EntryComponent::WeaponInfo* weapon);

		};
		class FiringCallbacks //: public dice::WeaponFiringCallbacks
		{
		public:
			EntryComponent& m_entry; // Offset = this + 0x4 Length = 0x4
			EntryComponent::WeaponInfo* m_info; // Offset = this + 0x8 Length = 0x4
		};

		//typedef eastl::vector<dice::EntryComponent::FiringCallbacks *,eastl::allocator> WeaponVector;
		//typedef eastl::set<dice::EntryComponent::Subscriber *,eastl::less<dice::EntryComponent::Subscriber *>,eastl::allocator> SubscriberSet;

		virtual void dtor();
		virtual fb::LinearTransform& soldierTransform();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual bool isOccupied();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual class AnimTreeDataAsset* animTree();
		virtual void setAnimHandsTransform(LinearTransform& transform);
		virtual void setAnimYaw(float yaw);
		virtual void setAnimPitch(float pitch);
		virtual void setAnimRoll(float roll);
		virtual bool useUpperBodyRotation();
		virtual void subscribe(EntryComponent::Subscriber* cb);
		virtual void unsubscribe(EntryComponent::Subscriber* cb);
		virtual void onUnSpawn();
		virtual void onPrimaryStartedFiring(EntryComponent::WeaponInfo* weapon);
		virtual void onPrimaryFire(EntryComponent::WeaponInfo* weapon);
		virtual void onPrimaryFireRelease(EntryComponent::WeaponInfo* weapon);
		virtual void onPrimaryFireShotSpawned(EntryComponent::WeaponInfo* weapon, float powerModifier);
		virtual void onPrimaryFireAutomaticBegin(EntryComponent::WeaponInfo* weapon);
		virtual void onPrimaryFireAutomaticEnd(EntryComponent::WeaponInfo* weapon);
		virtual void onPrimaryStoppedFiring(EntryComponent::WeaponInfo* weapon);
		virtual void onReload(EntryComponent::WeaponInfo* weapon);
		virtual void onWeaponAdded(EntryComponent::WeaponInfo* weapon);
		virtual void onWeaponRemoved(EntryComponent::WeaponInfo* weapon);
		virtual class EntryComponentData& entryData();	//TODO: Pure Function, update params from non-abstract derived class!

		eastl::vector< EntryComponent::FiringCallbacks* >  m_weapons; // Offset = this + 0x10 Length = 0x10
		//eastl::set<dice::EntryComponent::Subscriber *,eastl::less<dice::EntryComponent::Subscriber *>,eastl::allocator>  m_subscribers; // Offset = this + 0x20 Length = 0x1C
		//dice::physics::CharacterPoseConstraints* m_poseConstraints; // Offset = this + 0x3C Length = 0x4
		fb::LinearTransform  m_soldierTransform; // Offset = this + 0x40 Length = 0x40
		bool m_underExternalControl; // Offset = this + 0x80 Length = 0x1
	};

}
#endif /* _ENTRY_COMPONENT_H_ */ 