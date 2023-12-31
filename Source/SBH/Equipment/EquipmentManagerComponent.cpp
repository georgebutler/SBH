﻿#include "EquipmentManagerComponent.h"

#include "EquipmentData.h"
#include "EquipmentInstance.h"
#include "GameFramework/Character.h"
#include "SBH/SBHLogChannels.h"
#include "SBH/Inventory/InventoryComponent.h"

UEquipmentManagerComponent::UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UEquipmentManagerComponent::Equip(UItemData* ItemData)
{
	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
	UEquipmentData* EquipmentData = Cast<UEquipmentData>(ItemData);

	if (!EquipmentData || !OwningCharacter) 
	{
		return;
	}

	switch (EquipmentData->EquipmentSlot)
	{
	case EEquipmentSlot::Helmet:
		EquipItem(EquipmentData, EquippedHelmet, OwningCharacter);
		break;
	case EEquipmentSlot::Armor:
		EquipItem(EquipmentData, EquippedArmor, OwningCharacter);
		break;
	case EEquipmentSlot::Grenade:
		EquipItem(EquipmentData, EquippedGrenade, OwningCharacter);
		break;
	case EEquipmentSlot::Consumable:
		EquipItem(EquipmentData, EquippedConsumable, OwningCharacter);
		break;
	case EEquipmentSlot::Weapon:
		EquipWeapon(EquipmentData, OwningCharacter);
		break;
	default:
		break;
	}
}

void UEquipmentManagerComponent::Unequip(UItemData* ItemData)
{
	UEquipmentData* EquipmentData = Cast<UEquipmentData>(ItemData);

	if (!EquipmentData) 
	{
		return;
	}

	switch (EquipmentData->EquipmentSlot)
	{
	case EEquipmentSlot::Helmet:
		UnequipItem(EquippedHelmet, EquipmentData);
		break;
	case EEquipmentSlot::Armor:
		UnequipItem(EquippedArmor, EquipmentData);
		break;
	case EEquipmentSlot::Grenade:
		UnequipItem(EquippedGrenade, EquipmentData);
		break;
	case EEquipmentSlot::Consumable:
		UnequipItem(EquippedConsumable, EquipmentData);
		break;
	case EEquipmentSlot::Weapon:
		UnequipWeapon(EquipmentData);
		break;
	default:
		break;
	}
}

void UEquipmentManagerComponent::EquipItem(UEquipmentData* EquipmentData, FEquippedItem& Slot, ACharacter* OwningCharacter)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("EquipItem called with EquipmentData: %s, Slot: %s, OwningCharacter: %s"), *EquipmentData->ToString(), *Slot.ToString(), *OwningCharacter->GetName());
	
	if (Slot.Instance) 
	{
		UnequipItem(Slot, Slot.Data);
	}

	Slot.Instance = NewObject<AEquipmentInstance>(this, EquipmentData->SoftClassPtr.LoadSynchronous());
	Slot.Instance->Equip(OwningCharacter);
	Slot.Data = EquipmentData;
}

void UEquipmentManagerComponent::EquipWeapon(UEquipmentData* EquipmentData, ACharacter* OwningCharacter)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("EquipWeapon called with EquipmentData: %s, OwningCharacter: %s"), *EquipmentData->ToString(), *OwningCharacter->GetName());
	
	if (!EquippedPrimaryWeapon.Instance)
	{
		EquipItem(EquipmentData, EquippedPrimaryWeapon, OwningCharacter);
	}
	else if (EquippedPrimaryWeapon.Instance && !EquippedSecondaryWeapon.Instance)
	{
		EquipItem(EquipmentData, EquippedSecondaryWeapon, OwningCharacter);
	}
	else
	{
		EquipItem(EquipmentData, EquippedPrimaryWeapon, OwningCharacter);
	}
}

void UEquipmentManagerComponent::UnequipItem(FEquippedItem& Slot, UEquipmentData* EquipmentData)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("UnequipItem called with Slot: %s, EquipmentData: %s"), *Slot.ToString(), *EquipmentData->ToString());
	
	if (Slot.Instance && Slot.Data == EquipmentData)
	{
		Slot.Instance->Unequip();
		Slot.Instance = nullptr;
		Slot.Data = nullptr;
	}
}

void UEquipmentManagerComponent::UnequipWeapon(UEquipmentData* EquipmentData)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("UnequipWeapon called with EquipmentData: %s"), *EquipmentData->ToString());
	
	if (EquippedPrimaryWeapon.Data == EquipmentData)
	{
		UnequipItem(EquippedPrimaryWeapon, EquipmentData);
	}
	else if (EquippedSecondaryWeapon.Data == EquipmentData)
	{
		UnequipItem(EquippedSecondaryWeapon, EquipmentData);
	}
}
