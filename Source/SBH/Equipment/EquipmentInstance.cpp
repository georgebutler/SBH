#include "EquipmentInstance.h"

#include "GameFramework/Character.h"
#include "SBH/SBHLogChannels.h"

AEquipmentInstance::AEquipmentInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEquipmentInstance::Unequip_Implementation(ACharacter* Character)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("Unequip on %s called with Character: %s"), *GetName(), *Character->GetName());
	
	Destroy();
}

void AEquipmentInstance::Equip_Implementation(ACharacter* Character)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("Equip on %s called with Character: %s"), *GetName(), *Character->GetName());
	
	SetActorEnableCollision(false);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, AttachmentSocket);
}
