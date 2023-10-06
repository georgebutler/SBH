#include "EquipmentInstance.h"

#include "SBH/SBHLogChannels.h"

AEquipmentInstance::AEquipmentInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEquipmentInstance::Unequip_Implementation(ACharacter* Character)
{
	UE_LOG(LogSBH, Log, TEXT("Unequipped Item"));
}

void AEquipmentInstance::Equip_Implementation(ACharacter* Character)
{
	UE_LOG(LogSBH, Log, TEXT("Equipped Item"));
}
