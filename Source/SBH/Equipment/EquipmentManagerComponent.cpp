#include "EquipmentManagerComponent.h"

#include "EquipmentData.h"
#include "EquipmentInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SBH/Inventory/InventoryComponent.h"

UEquipmentManagerComponent::UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UEquipmentManagerComponent::Equip(UItemData* ItemData, const bool bRequiresInInventory)
{
	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
	UInventoryComponent* InventoryComponent = UInventoryComponent::FindInventoryComponent(OwningCharacter);

	if (InventoryComponent)
	{
		if (bRequiresInInventory)
		{
			const FInventoryItem FoundItem = InventoryComponent->GetItem(ItemData);

			if (FoundItem.Data)
			{
				const UEquipmentData* EquipmentData = Cast<UEquipmentData>(FoundItem.Data);
				AEquipmentInstance* EquipmentInstance = NewObject<AEquipmentInstance>(this, EquipmentData->SoftClassPtr.LoadSynchronous());

				EquipmentInstance->Equip(OwningCharacter);
			}
		}
		else
		{
			const UEquipmentData* EquipmentData = Cast<UEquipmentData>(ItemData);
			AEquipmentInstance* EquipmentInstance = NewObject<AEquipmentInstance>(this, EquipmentData->SoftClassPtr.LoadSynchronous());

			EquipmentInstance->Equip(OwningCharacter);
		}
	}
}

void UEquipmentManagerComponent::Unequip(UItemData* ItemData)
{
}
