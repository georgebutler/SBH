#include "EquipmentInstance.h"

AEquipmentInstance::AEquipmentInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEquipmentInstance::Unequip_Implementation(ACharacter* Character)
{
}

void AEquipmentInstance::Equip_Implementation(ACharacter* Character)
{
}
